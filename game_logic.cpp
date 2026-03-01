#include "game_logic.h"
#include <algorithm>
#include <ctime>

GameLogic::GameLogic() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            board[y][x] = 0;
        }
    }
    spawnPiece();
}

void GameLogic::spawnPiece() {
    m_curPiece = Tetromino(static_cast<TetrominoType>((std::rand() % 7) + 1));
    m_x = WIDTH / 2 - 1;
    m_y = 0;

    if (checkCollision(m_x, m_y, m_curPiece)) {
        for (int y = 0; y < HEIGHT; ++y)
            for (int x = 0; x < WIDTH; ++x) board[y][x] = 0;
    }
}

bool GameLogic::checkCollision(int nx, int ny, const Tetromino& piece) {
    for (auto p : piece.getPoints(nx, ny)) {
        if (p.x < 0 || p.x >= WIDTH || p.y >= HEIGHT) return true;
        if (p.y >= 0 && board[p.y][p.x] != 0) return true;
    }
    return false;
}

void GameLogic::moveLeft() {
    if (!checkCollision(m_x - 1, m_y, m_curPiece)) m_x--;
}

void GameLogic::moveRight() {
    if (!checkCollision(m_x + 1, m_y, m_curPiece)) m_x++;
}

bool GameLogic::moveDown() {
    if (!checkCollision(m_x, m_y + 1, m_curPiece)) {
        m_y++;
        return true;
    } else {
        freezePiece();
        return false;
    }
}

void GameLogic::rotate() {
    Tetromino rotated = m_curPiece;
    rotated.rotate();
    if (!checkCollision(m_x, m_y, rotated)) {
        m_curPiece = rotated;
    }
}

void GameLogic::freezePiece() {
    for (auto p : m_curPiece.getPoints(m_x, m_y)) {
        if (p.y >= 0) board[p.y][p.x] = static_cast<int>(m_curPiece.type());
    }
    clearLines();
    spawnPiece();
}

void GameLogic::clearLines() {
    for (int y = HEIGHT - 1; y >= 0; --y) {
        bool isFull = true;
        for (int x = 0; x < WIDTH; ++x) {
            if (board[y][x] == 0) {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            for (int ty = y; ty > 0; --ty) {
                for (int tx = 0; tx < WIDTH; ++tx) {
                    board[ty][tx] = board[ty - 1][tx];
                }
            }
            for (int tx = 0; tx < WIDTH; ++tx) board[0][tx] = 0;
            y++;
        }
    }
}
