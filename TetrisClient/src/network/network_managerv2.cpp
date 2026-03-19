#include "network_managerv2.h"
#include <QNetworkAccessManager>
#include <qsslconfiguration.h>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
NetworkManagerV2 &NetworkManagerV2::instance()
{
    static NetworkManagerV2 instance;
    return instance;
}


void NetworkManagerV2::post(const QUrl& url,
                            const QByteArray& data,
                            std::function<void(QNetworkReply*)> callback)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        callback(reply);
        reply->deleteLater();
    });
}
bool NetworkManagerV2::createAccount(QString nickname, QString password)
{
    // QUrl url("https://127.0.0.1:8443/api/login");
    // QNetworkRequest request(url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // QJsonObject json;
    // json["username"] = nickname;
    // json["password"] = password;
    // QByteArray data = QJsonDocument(json).toJson();

    // qDebug() << "Отправка запроса на авторизацию...";
    // manager->post(request, data);
    return 1;
}

bool NetworkManagerV2::loginInAccount(QString nickname, QString password)
{
    // QUrl url("https://127.0.0.1:8443/api/login");
    // QNetworkRequest request(url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // QJsonObject json;
    // json["username"] = nickname;
    // json["password"] = password;
    // QByteArray data = QJsonDocument(json).toJson();

    // qDebug() << "Отправка запроса на авторизацию...";
    // manager->post(request, data);
    // return 1;
QJsonObject json;
    json["login"]    = nickname; // ключ должен совпадать с сервером
    json["password"] = password;

    post(QUrl("https://127.0.0.1:8443/api/login"),
         QJsonDocument(json).toJson(),
         [this](QNetworkReply* reply)
    {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Network error:" << reply->errorString();
            emit loginFailed(reply->errorString());
            return;
        }

        auto doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isObject()) {
            emit loginFailed("Invalid response");
            return;
        }

        auto obj = doc.object();
        if (obj.contains("token")) {
            token = obj["token"].toString();
            qDebug() << "Login OK, token:" << token;
            emit loginSuccess(token);
        } else {
            emit loginFailed(obj["error"].toString());
        }
});
    return 1;
}

NetworkManagerV2::NetworkManagerV2(QObject *parent): QObject(parent)
{
    initQManager();

}

bool NetworkManagerV2::initQManager()
{
    manager=new QNetworkAccessManager();
    manager->setParent(this);
    connect(manager, &QNetworkAccessManager::sslErrors,
            this, [](QNetworkReply* reply, const QList<QSslError>& errors) {
                qWarning() << "SSL errors (ignored for localhost):" << errors;
                reply->ignoreSslErrors();
            });
    return 1;
}
