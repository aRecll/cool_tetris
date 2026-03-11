#include "mainwindow.h"
#include "game_widget.h"
#include "setting_manager.h"
#include "network_manager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


void MainWindow::debuqqq(){
    gameWidget->fildWidget->getLogic().getLinesCleared();

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    SettingsManager::instance().loadSettings();
    stackedWidget = new QStackedWidget(this);

    menuWidget = new MenuWidget(this);
    gameWidget = new GameWidget(this);

    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    setCentralWidget(stackedWidget);

    connect(menuWidget, &MenuWidget::onStartClicked, this, &MainWindow::onStartClicked);
   // connect(menuWidget, &MenuWidget::onExitClicked, SettingsManager::instance(), &SettingsManager::writeSettings);
    connect(menuWidget, &MenuWidget::onExitClicked, this, &MainWindow::close);
    connect(gameWidget, &GameWidget::escapePressed, this, &MainWindow::escClicked);
    connect(gameWidget,&GameWidget::gameEnd,this,&MainWindow::onGameEnd);
   // connect(gameWidget->fildWidget->getLogic(),&GameLogic::scoreChanged,this,&MainWindow::debuqqq);
   // connect(gameWidget, &GameWidget::gameEnd,this,&MainWindow::updateScores);
}

void MainWindow::onStartClicked() {
   // gameWidget->fildWidget->getLogic().start();
    stackedWidget->setCurrentIndex(1);
    gameWidget->restart();
    gameWidget->setFocus();
}

void MainWindow::escClicked() {

    // if (!gameWidget->fildWidget->getLogic().isPaused()) {
    //     gameWidget->fildWidget->getLogic().pause();
    // }
    //gameWidget->restart();
    gameWidget->clearFocus();
    stackedWidget->setCurrentIndex(0);
    menuWidget->setFocus();
}

void MainWindow::onGameEnd()
{
    SettingsManager::instance().updateTotalyCoutLines(gameWidget->fildWidget->getLogic().getLinesCleared());
    SettingsManager::instance().updateMaxScore(gameWidget->fildWidget->getLogic().getScore());
    SettingsManager::instance().updateCountGames();
    SettingsManager::instance().saveSettings();
    // scoresChanged() вызывается внутри updateTotalyCoutLines и updateMaxScore





    NetworkManager::instance().sendScore(
        SettingsManager::instance().nickname(),
        gameWidget->fildWidget->getLogic().getScore(),
        gameWidget->fildWidget->getLogic().getLinesCleared()
        );
}

// void MainWindow::updateScores()
// {
//     SettingsManager::instance().updateTotalyCoutLines(gameWidget->fildWidget->getLogic().getLinesCleared());
//     SettingsManager::instance().updateMaxScore(gameWidget->fildWidget->getLogic().getScore());
//     SettingsManager::instance().writeSettings();
// }
