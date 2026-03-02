#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QSet>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "game_logic.h"
#include <QElapsedTimer>
class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void gameStep();

signals:
    void escapePressed();
private:
    GameLogic m_game;
    QTimer *m_timer;
    QSet<int> pressedKeys;
    QTimer *inputTimer;
    const int CELL_SIZE = 30;
    void processInput();
    QElapsedTimer rotateTimer;
    const int ROTATE_COOLDOWN = 200;
};

#endif
