#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "game_widget.h"
#include "menu_widget.h"

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
    MenuWidget *menuWidget;

};

#endif // MAINWINDOW_H
