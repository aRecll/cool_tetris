#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <vector>
#include "tetromino.h"

class GameLogic : public QObject {
    Q_OBJECT
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    GameLogic();
    void moveLeft();
    void moveRight();
    bool moveDown(); // Возвращает false, если фигура зафиксирована
    void rotate();

    int getCell(int x, int y) const { return board[y][x]; }
    Tetromino curPiece() const { return m_curPiece; }
    Point curPos() const { return {m_x, m_y}; }

private:
    void spawnPiece();
    bool checkCollision(int dx, int dy, const Tetromino& piece);
    void freezePiece();
    void clearLines();

    int board[HEIGHT][WIDTH];
    Tetromino m_curPiece;
    int m_x, m_y;
    int m_score = 0;
};

#endif
