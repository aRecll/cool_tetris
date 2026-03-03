#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "game_widget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onStartClicked();
    void escClicked();
private:
    QStackedWidget *stackedWidget;
    GameWidget * gameWidget;
    QWidget *menuWidget;
    QPushButton *btnStart;
    QPushButton *btnExit ;
};

#endif // MAINWINDOW_H
