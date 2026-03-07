#include "mainwindow.h"
#include "game_widget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);

    menuWidget = new MenuWidget(this);
    gameWidget = new GameWidget(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    setCentralWidget(stackedWidget);

    connect(menuWidget, &MenuWidget::onStartClicked, this, &MainWindow::onStartClicked);
    connect(menuWidget, &MenuWidget::onExitClicked, this, &MainWindow::close);
    connect(gameWidget, &GameWidget::escapePressed, this, &MainWindow::escClicked);
}

void MainWindow::onStartClicked() {
   // gameWidget->fildWidget->getLogic().start();
    stackedWidget->setCurrentIndex(1);
    gameWidget->setFocus();

}

void MainWindow::escClicked() {

    // if (!gameWidget->fildWidget->getLogic().isPaused()) {
    //     gameWidget->fildWidget->getLogic().pause();
    // }
    gameWidget->clearFocus();
    stackedWidget->setCurrentIndex(0);
    menuWidget->setFocus();
}
