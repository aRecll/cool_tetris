#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QSet>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "game_logic.h"
#include <QElapsedTimer>
class FildWidget : public QWidget {
    Q_OBJECT
public:
    FildWidget(QWidget *parent = nullptr);
    const GameLogic& getLogic() const { return m_game; };

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
     int CELL_SIZE;
    void processInput();
    QElapsedTimer rotateTimer;
    const int ROTATE_COOLDOWN = 200;
};

#endif
