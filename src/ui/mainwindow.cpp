#include "mainwindow.h"
#include "game_widget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);


    menuWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(menuWidget);
    gameWidget=new GameWidget(this);
    QLabel *title = new QLabel("QT TETRIS");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px;");
    title->setAlignment(Qt::AlignCenter);

    btnStart = new QPushButton("ИГРАТЬ");
    btnExit = new QPushButton("ВЫХОД");


    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(btnStart);
    layout->addWidget(btnExit);
    layout->addStretch();
    layout->setAlignment(Qt::AlignCenter);








    stackedWidget->addWidget(menuWidget);
    stackedWidget->addWidget(gameWidget);

    setCentralWidget(stackedWidget);


    connect(btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::close);

    connect(gameWidget, &GameWidget::escapePressed, this, &MainWindow::escClicked);


}

void MainWindow::onStartClicked() {
    stackedWidget->setCurrentIndex(1);
    gameWidget->setFocus();


}

void MainWindow::escClicked() {
    gameWidget->clearFocus();
    stackedWidget->setCurrentIndex(0);
    menuWidget ->setFocus();

    btnStart->setFocus(Qt::OtherFocusReason);

}
