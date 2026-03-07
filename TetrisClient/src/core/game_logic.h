#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <vector>
#include <deque>
#include <QTimer>
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
    int getScore() const {return score;}
    

    void start();
    void pause();
    void resume();
    void restart();
    bool isPaused() const { return m_isPaused; }
    bool isGameEnd() const { return m_isGameEnd; }
    

    int getLevel() const { return level; }
    int getLinesCleared() const { return totalLines; }
    int getInterval() const { return currentInterval; }


signals:
    void nextPiecesChanged();
    void pocketChanged();
    void scoreChanged();
    void levelChanged(int newLevel);
    void tick();
    void gameEnd();

private slots:
    void onTimerTick();

private:
    void spawnPiece();
    bool checkCollision(int dx, int dy, const Tetromino& piece);
    void freezePiece();
    void clearLines();
    void updateScoreLine(int countLines);
    void updateScoreDrope(bool isDropDown);
    void updateSpeed();
    int calculateInterval(int lvl);
    void collapseGame();
    int score;
    int board[HEIGHT][WIDTH];
    Tetromino m_curPiece;
    Tetromino m_poketPiece;
    bool m_canSwap;
    int m_x, m_y;

    std::deque<Tetromino> m_nextPieces;
    

    QTimer *m_timer;
    bool m_isPaused;
    bool m_isGameEnd;
    int level;
    int totalLines;
    int linesToNextLevel;
    int currentInterval;
};

#endif
