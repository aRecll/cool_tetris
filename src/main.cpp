#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // Твой рандом остается
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    QApplication app(argc, argv);


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
