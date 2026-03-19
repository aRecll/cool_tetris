#ifndef NETWORK_MANAGERV2_H
#define NETWORK_MANAGERV2_H
#include <QObject>
#include <QString>
class  QNetworkAccessManager;
class QNetworkReply;
class NetworkManagerV2 : public QObject
{
    Q_OBJECT
public:
    static NetworkManagerV2& instance();
    //NetworkManagerV2() =delete;
    bool createAccount(QString nickname,QString password);
    bool loginInAccount(QString nickname,QString password);
signals:
    void loginSuccess(QString token);
    void loginFailed(QString err);
private:

    NetworkManagerV2(QObject* parent = nullptr);
    bool initQManager();
    void post(const QUrl& url,
              const QByteArray& data,
              std::function<void(QNetworkReply*)> callback);
    QString token;
    QNetworkAccessManager* manager=nullptr;
};

#endif // NETWORK_MANAGERV2_H
