#include <QApplication>
#include "game_widget.h"
#include <ctime>

int main(int argc, char *argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    QApplication app(argc, argv);

    GameWidget window;
    window.setWindowTitle("Qt Tetris");
    window.show();

    return app.exec();
}
