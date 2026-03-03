#ifndef NEXT_PIECES_WIDGET_H
#define NEXT_PIECES_WIDGET_H

#include <QWidget>
#include <QPainter>
#include "game_logic.h"

class NextPiecesWidget : public QWidget {
    Q_OBJECT
public:
    NextPiecesWidget(const GameLogic &game, QWidget *parent = nullptr)
        : QWidget(parent), m_game(game) {
        setFixedSize(120, 300);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        auto next = m_game.getNextPieces();
        int cellSize = 25;

        for (int i = 0; i < 3; ++i) {
            Tetromino piece = next[i];
            painter.setBrush(piece.color());

            for (auto p : piece.getPoints(2, i * 4 + 2)) {
                painter.drawRect(p.x * cellSize, p.y * cellSize, cellSize - 1, cellSize - 1);
            }
        }
    }

private:
    const GameLogic &m_game;
};

#endif // NEXT_PIECES_WIDGET_H
