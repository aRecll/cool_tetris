#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <vector>
#include <deque>
#include "tetromino.h"

class GameLogic : public QObject {
    Q_OBJECT
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    GameLogic();
    void moveLeft();
    void moveRight();
    bool moveDown();
    void rotate();
    void instaMoveDown();

    int getCell(int x, int y) const { return board[y][x]; }
    std::vector<Tetromino>getNextPieces() const ;
    Tetromino curPiece() const { return m_curPiece; }
    Point curPos() const { return {m_x, m_y}; }
    void swapPoketPiece();
    Tetromino getPoketPiece() const{return m_poketPiece;}
signals:
    void nextPiecesChanged();
    void pocketChanged();
private:
    void spawnPiece();
    bool checkCollision(int dx, int dy, const Tetromino& piece);
    void freezePiece();
    void clearLines();



    int board[HEIGHT][WIDTH];
    Tetromino m_curPiece;
    Tetromino m_poketPiece;
    bool m_canSwap;
    int m_x, m_y;
    int m_score = 0;
    std::deque<Tetromino> m_nextPieces;
};

#endif
