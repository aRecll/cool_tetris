#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "game_logic.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void gameStep();

private:
    GameLogic m_game;
    QTimer *m_timer;
    const int CELL_SIZE = 30;
};

#endif
