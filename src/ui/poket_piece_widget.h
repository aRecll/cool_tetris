#ifndef POKET_PIECE_WIDGET_H
#define POKET_PIECE_WIDGET_H

#include <QWidget>
#include <QPainter>
#include "game_logic.h"
class PoketPieceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PoketPieceWidget(const GameLogic &game, QWidget *parent = nullptr)
        : QWidget(parent), m_game(game) {
        setFixedSize(120, 120);
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        Tetromino poket = m_game.getPoketPiece();
        int cellSize = 25;



        for (auto p : poket.getPoints(2,  2)) {
            painter.drawRect(p.x * cellSize, p.y * cellSize, cellSize - 1, cellSize - 1);
        }

    }



private:
    const GameLogic &m_game;
};

#endif // POKET_PIECE_WIDGET_H
