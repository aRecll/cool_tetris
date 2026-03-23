#include <QCoreApplication>
#include <QHttpServer>
#include <QSslServer>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QSslKey>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>

static QMap<QString, int> s_tokens;

int db_validateUser(const QString& login, const QString& pass) {
    if (login == "admin" && pass == "secret123") return 1;
    if (login == "user"  && pass == "pass456")   return 2;
    return -1;
}

QString db_createToken(int userId) {
    // TODO: INSERT INTO sessions ...
    QString token = QUuid::createUuid().toString(QUuid::WithoutBraces);
    s_tokens[token] = userId;
    return token;
}

int db_validateToken(const QString& token) {
    // TODO: SELECT user_id FROM sessions WHERE token=? AND expires_at > NOW()
    return s_tokens.value(token, -1);
}
bool connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    // "db" — это имя сервиса из твоего docker-compose.yml
    // Если запускаешь локально (не в докере), поменяй на "localhost"
    QString host = qEnvironmentVariable("DB_HOST", "localhost");
    QString name = qEnvironmentVariable("DB_NAME", "my_database");
    QString user = qEnvironmentVariable("DB_USER", "user");
    QString pass = qEnvironmentVariable("DB_PASS", "password");
    int port     = qEnvironmentVariable("DB_PORT", "5432").toInt();

    db.setHostName(host);
    db.setDatabaseName(name);
    db.setUserName(user);
    db.setPassword(pass);
    db.setPort(port);

    if (!db.open()) {
        qCritical() << "Ошибка подключения к БД:" << db.lastError().text();
        return false;
    }

    qInfo() << "Успешное подключение к PostgreSQL на хосте:" << host;
    return true;
}

// redisContext* connectToRedis() {
//     // Аналогично: "redis" — имя сервиса из docker-compose
//     const char* hostname = "redis";
//     int port = 6379;

//     redisContext* c = redisConnect(hostname, port);

//     if (c == nullptr || c->err) {
//         if (c) {
//             std::cerr << "Ошибка Redis: " << c->errstr << std::endl;
//             redisFree(c);
//         } else {
//             std::cerr << "Не удалось выделить контекст Redis" << std::endl;
//         }
//         return nullptr;
//     }

//     std::cout << "Успешное подключение к Redis!" << std::endl;
//     return c;
// }
int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QHttpServer server;

    // POST /api/login
    connectToDatabase();
    server.route("/", QHttpServerRequest::Method::Get,
                 []() -> QHttpServerResponse
                 {
                     QFile file(":/index.html");
                     if (!file.open(QIODevice::ReadOnly))
                         return QHttpServerResponse(
                             QJsonObject{{"error", "index.html not found"}},
                             QHttpServerResponse::StatusCode::NotFound);

                     return QHttpServerResponse("text/html; charset=utf-8", file.readAll());
                 });

    server.route("/api/login", QHttpServerRequest::Method::Post,
                 [](const QHttpServerRequest& req) -> QHttpServerResponse
                 {
                     QJsonParseError err;
                     auto doc = QJsonDocument::fromJson(req.body(), &err);
                     if (err.error != QJsonParseError::NoError || !doc.isObject())
                         return QHttpServerResponse(
                             QJsonObject{{"error", "Invalid JSON"}},
                             QHttpServerResponse::StatusCode::BadRequest);

                     auto obj      = doc.object();
                     QString login = obj["login"].toString().trimmed();
                     QString pass  = obj["password"].toString();

                     if (login.isEmpty() || pass.isEmpty())
                         return QHttpServerResponse(
                             QJsonObject{{"error", "login and password required"}},
                             QHttpServerResponse::StatusCode::BadRequest);

                     int userId = db_validateUser(login, pass);
                     if (userId < 0)
                         return QHttpServerResponse(
                             QJsonObject{{"error", "Invalid credentials"}},
                             QHttpServerResponse::StatusCode::Unauthorized);

                     return QHttpServerResponse(QJsonObject{
                         {"message", "Login successful"},
                         {"token",   db_createToken(userId)},
                         {"userId",  userId}
                     });
                 });

    // GET /api/protected
    server.route("/api/protected", QHttpServerRequest::Method::Get,
                 [](const QHttpServerRequest& req) -> QHttpServerResponse
                 {
                     QString auth = req.value("Authorization");
                     if (!auth.startsWith("Bearer ", Qt::CaseInsensitive))
                         return QHttpServerResponse(
                             QJsonObject{{"error", "Missing token"}},
                             QHttpServerResponse::StatusCode::Unauthorized);

                     int userId = db_validateToken(auth.mid(7).trimmed());
                     if (userId < 0)
                         return QHttpServerResponse(
                             QJsonObject{{"error", "Invalid or expired token"}},
                             QHttpServerResponse::StatusCode::Unauthorized);

                     return QHttpServerResponse(QJsonObject{
                         {"message", QString("Hello, user #%1!").arg(userId)},
                         {"userId",  userId}
                     });
                 });

    // ── HTTPS: QSslServer + bind() ────────────────────────
    QFile certFile(":/cert.pem"), keyFile(":/key.pem");
    // Проверяем что файлы вообще видны в QRC
    qDebug() << "cert exists:" << certFile.exists();
    qDebug() << "key exists:"  << keyFile.exists();

    if (!certFile.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open cert:" << certFile.errorString();
        return -1;
    }
    if (!keyFile.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open key:" << keyFile.errorString();
        return -1;
    }
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);

    QByteArray certData = certFile.readAll();
    QByteArray keyData  = keyFile.readAll();
    certFile.close();
    keyFile.close();
    //certFile.open(QIODevice::ReadOnly);
    //keyFile.open(QIODevice::ReadOnly);

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setLocalCertificate(QSslCertificate(certData, QSsl::Pem));
    sslConfig.setPrivateKey(QSslKey(keyData, QSsl::Rsa, QSsl::Pem));
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfig.setProtocol(QSsl::TlsV1_2OrLater);


    auto* sslServer = new QSslServer();
    sslServer->setSslConfiguration(sslConfig);
    int server_port     = qEnvironmentVariable("SERVER_PORT", "8443").toInt();
    if (!sslServer->listen(QHostAddress::Any, server_port  ))

    {
        qCritical() << "Failed to start HTTPS server";
        delete sslServer;
        return -1;
    }
    server.bind(sslServer);
    qInfo() << "HTTPS server on https://127.0.0.1:" << sslServer->serverPort();
    return app.exec();
}


// #include <QCoreApplication>
// #include <QHttpServer>
// #include <QHttpServerResponse>
// #include <QJsonObject>
// #include <QJsonDocument>
// #include <QLoggingCategory>
// #include <QTcpServer>


// struct User {
//     QString username;
//     QString password;
//     QString token;
// };

// class MySecureServer : public QObject {
//     Q_OBJECT
// public:
//     MySecureServer() {
//         // Наполняем нашу "базу данных"
//         users["admin"] = {"admin", "12345", "token-secret-123"};
//         users["user"]  = {"user", "password", "token-guest-456"};

//         setupRoutes();
//     }

//     bool start(quint16 port) {
//         // 1. Создаем стандартный TCP сервер
//         tcpServer = new QTcpServer(this);

//         // 2. Начинаем слушать порт
//         if (!tcpServer->listen(QHostAddress::Any, port)) {
//             qCritical() << "Could not start TCP server:" << tcpServer->errorString();
//             return false;
//         }

//         // 3. Привязываем HTTP-логику к этому TCP-серверу
//         if (!server.bind(tcpServer)) {
//             qCritical() << "Could not bind HTTP server to TCP server";
//             return false;
//         }

//         qDebug() << "HTTP Server is running on port:" << tcpServer->serverPort();
//         return true;
//     }

// private:
//     QHttpServer server;
//     QTcpServer* tcpServer = nullptr;
//     QMap<QString, User> users; /

//     void setupRoutes() {
//
//         server.route("/api/v1/login", QHttpServerRequest::Method::Post,
//                      [this](const QHttpServerRequest &request) {

//                          QJsonDocument doc = QJsonDocument::fromJson(request.body());
//                          if (doc.isNull() || !doc.isObject()) {
//                              return QHttpServerResponse(QJsonObject{{"error", "Invalid JSON"}},
//                                                         QHttpServerResponse::StatusCode::BadRequest);
//                          }

//                          QJsonObject body = doc.object();
//                          QString user = body["username"].toString();
//                          QString pass = body["password"].toString();

//                          qDebug() << "Login attempt for user:" << user;

//
//                          if (users.contains(user) && users[user].password == pass) {
//                              QJsonObject resp;
//                              resp["status"] = "success";
//                              resp["token"] = users[user].token;
//                              return QHttpServerResponse(resp); // По умолчанию 200 OK
//                          }

//                          return QHttpServerResponse(QJsonObject{{"message", "Unauthorized"}},
//                                                     QHttpServerResponse::StatusCode::Unauthorized);
//                      });

//
//         server.route("/api/v1/profile", QHttpServerRequest::Method::Get,
//                      [this](const QHttpServerRequest &request) {

//                          // Извлекаем заголовок Authorization
//                          auto authHeader = request.value("Authorization").toStdString();

//                          // Ищем пользователя по токену в нашей "базе"
//                          for (const auto &user : users) {
//                              if ("Bearer " + user.token == authHeader) {
//                                  QJsonObject profile;
//                                  profile["username"] = user.username;
//                                  profile["role"] = (user.username == "admin" ? "administrator" : "viewer");
//                                  return QHttpServerResponse(profile);
//                              }
//                          }

//                          return QHttpServerResponse(QHttpServerResponse::StatusCode::Unauthorized);
//                      });

//
//         server.route("/api/v1/settings", QHttpServerRequest::Method::Put,
//                      [](const QHttpServerRequest &request) {
//                          qDebug() << "Updating settings with body:" << request.body();
//                          return QHttpServerResponse(QJsonObject{{"status", "updated"}});
//                      });
//     }
// };

// int main(int argc, char *argv[]) {
//     QCoreApplication app(argc, argv);
//     MySecureServer server;
//     if (!server.start(8080)) return -1;
//     return app.exec();
// }




// #include <QCoreApplication>
// #include <QTcpServer>
// #include <QTcpSocket>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QDebug>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>
//     #include <QFileInfo>
// //#include "qjsonwebtoken.h"
// class SimpleServer : public QTcpServer {
//     Q_OBJECT
// public:
//     SimpleServer(QObject *parent = nullptr) : QTcpServer(parent) {}

// protected:
//     void incomingConnection(qintptr socketDescriptor) override {
//         QTcpSocket* socket = new QTcpSocket(this);
//         socket->setSocketDescriptor(socketDescriptor);

//         qDebug() << "Клиент подключился:" << socket->peerAddress().toString();

//         connect(socket, &QTcpSocket::readyRead, this, [socket]() {
//             QByteArray data = socket->readAll();


//             QJsonDocument doc = QJsonDocument::fromJson(data.trimmed());
//             if (doc.isNull() || !doc.isObject()) {
//                 qDebug() << "Ошибка: Получены некорректные данные";
//                 return;
//             }

//             QJsonObject json = doc.object();
//             QString nickname = json["nickname"].toString();
//             int score = json["score"].toInt();

//             qDebug() << "Данные игрока -> Имя:" << nickname << "Счёт:" << score;


//             QSqlQuery query;
//             query.prepare("INSERT INTO TopResults (nickname, BestScore) VALUES (:name, :score)");
//             query.bindValue(":name", nickname);
//             query.bindValue(":score", score);

//             if (!query.exec()) {
//                 qDebug() << "Ошибка записи в БД:" << query.lastError().text();
//                 socket->write("ERROR\n");
//             } else {
//                 qDebug() << "Запись успешно добавлена";
//                 socket->write("OK\n");
//             }
//         });

//         connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
//         connect(socket, &QTcpSocket::disconnected, []() {
//             qDebug() << "Клиент отключился";
//         });
//     }
// };

// int main(int argc, char *argv[]) {
//     QCoreApplication app(argc, argv);

//    // QJsonWebToken tk=QJsonWebToken
//     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//     db.setDatabaseName("testDB.db");

//     if (!db.open()) {
//         qDebug() << "Критическая ошибка: не удалось открыть БД:" << db.lastError().text();
//         return -1;
//     }
//     qDebug() << "База данных подключена.";


//     QSqlQuery query;
//     bool tableOk = query.exec("CREATE TABLE IF NOT EXISTS TopResults ("
//                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                               "nickname TEXT, "
//                               "BestScore INT)");
//     if (!tableOk) {
//         qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
//     }


//     SimpleServer server;
//     if (!server.listen(QHostAddress::Any, 5000)) {
//         qDebug() << "Ошибка запуска сервера:" << server.errorString();
//         return 1;
//     }

//     qDebug() << "Сервер Tetris запущен на порту 5000";
//     qDebug() << "Путь к БД:" << QFileInfo(db.databaseName()).absoluteFilePath();
//     return app.exec();
// }
// #include "main.moc"

