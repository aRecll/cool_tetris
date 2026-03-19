#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "MainWindow.h"
#include "network_manager.h"
#include <QSslSocket>
#include <QSsl>

int main(int argc, char *argv[]) {
    qDebug() << "Qt runtime version:" << qVersion();          // из dll
    qDebug() << "Qt compile version:" << QT_VERSION_STR;
    qDebug() << "OpenSSL version:" << QSslSocket::sslLibraryVersionString();
    qDebug() << "SSL supported:"   << QSslSocket::supportsSsl();
    qDebug() <<QSslSocket::availableBackends();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("s7shvets7s");
    QCoreApplication::setApplicationName("cool_tetris");
    app.setWindowIcon(QIcon(":/app_icon.ico"));
    NetworkManager::instance().setServerAddress("127.0.0.1", 5000);

        // Подключение для отладки
    QObject::connect(&NetworkManager::instance(), &NetworkManager::sendSuccess,
                     [](){ qDebug() << "Статистика отправлена!"; });
    QObject::connect(&NetworkManager::instance(), &NetworkManager::sendError,
                     [](const QString& err){ qDebug() << "Ошибка отправки:" << err; });
    MainWindow window;

#ifdef Q_OS_ANDROID
    window.showMaximized();
#elif defined(Q_OS_IOS)
    window.showFullScreen();
#else

    window.resize(400, 700);
    window.show();
#endif

    return app.exec();
}
