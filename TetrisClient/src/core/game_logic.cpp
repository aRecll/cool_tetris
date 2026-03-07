#include "game_logic.h"
#include <algorithm>
#include <ctime>
#include <cmath>

GameLogic::GameLogic() {
    score = 0;
    level = 0;
    totalLines = 0;
    linesToNextLevel = 10;
    m_isPaused = false;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            board[y][x] = 0;
        }
    }
    for(int i = 0; i < 4; ++i) {
        m_nextPieces.push_back(Tetromino(static_cast<TetrominoType>((rand() % 7) + 1)));
    }
    spawnPiece();
    

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameLogic::onTimerTick);
    updateSpeed();
     start();
}

void GameLogic::start() {
    m_timer->start(currentInterval);
}

void GameLogic::pause() {
    if (!m_isPaused) {
        m_isPaused = true;
        m_timer->stop();
    }
}

void GameLogic::resume() {
    if (m_isPaused) {
        m_isPaused = false;
        m_timer->start(currentInterval);
    }
}

void GameLogic::restart()
{
    score = 0;
    level = 0;

    totalLines = 0;
    linesToNextLevel = 10;
    m_isPaused = false;
    m_isGameEnd=false;
    m_nextPieces.clear();
    m_poketPiece=Empty;


    emit pocketChanged();
    emit scoreChanged();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            board[y][x] = 0;
        }
    }
    for(int i = 0; i < 4; ++i) {
        m_nextPieces.push_back(Tetromino(static_cast<TetrominoType>((rand() % 7) + 1)));
    }
    spawnPiece();



    updateSpeed();
    start();
}

void GameLogic::onTimerTick() {
    moveDown();
    emit tick();
}

int GameLogic::calculateInterval(int lvl) {
    // Формула скорости как в классическом тетрисе (Nintendo)
    // Каждые 10 линий уровень повышается, скорость увеличивается
    // Минимальный интервал 16мс (около 60 FPS)
    if (lvl <= 0) return 1000;
    return std::max(16, (int)(1000 * std::pow(0.85, lvl)));
}

void GameLogic::collapseGame()
{
    pause();
    m_isGameEnd=true;
    emit gameEnd();
}

void GameLogic::updateSpeed() {
    currentInterval = calculateInterval(level);
    if (!m_isPaused) {
        m_timer->setInterval(currentInterval);
    }
}

void GameLogic::spawnPiece() {
    m_curPiece = m_nextPieces.front();
    m_nextPieces.pop_front();
    m_nextPieces.push_back(Tetromino(static_cast<TetrominoType>((rand() % 7) + 1)));
    m_x = WIDTH / 2 - 1;
    m_y = 0;
    m_canSwap=true;
    if (checkCollision(m_x, m_y, m_curPiece)) {
        collapseGame();
    }
    emit nextPiecesChanged();
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
        updateScoreDrope(false);
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

void GameLogic::instaMoveDown()
{
    while (!checkCollision(m_x, m_y + 1, m_curPiece)) {
        m_y++;
    }
    updateScoreDrope(true);
    freezePiece();
}

void GameLogic::freezePiece() {
    for (auto p : m_curPiece.getPoints(m_x, m_y)) {
        if (p.y >= 0) board[p.y][p.x] = static_cast<int>(m_curPiece.type());
    }
    clearLines();
    spawnPiece();
}

void GameLogic::clearLines() {
    int countLines=0;
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
            countLines+=1;
            for (int tx = 0; tx < WIDTH; ++tx) board[0][tx] = 0;
            y++;
        }
    }
    if (countLines > 0) {
        totalLines += countLines;

        if (totalLines >= linesToNextLevel) {
            level++;
            linesToNextLevel += 10;
            updateSpeed();
            emit levelChanged(level);
        }
        updateScoreLine(countLines);
    }
}

void GameLogic::updateScoreLine(int countLines)
{
    switch (countLines) {
    case 1: score+=100*(level+1); break;
    case 2: score+=300*(level+1); break;
    case 3: score+=500*(level+1); break;
    case 4: score+=1200*(level+1); break;
    default:
        break;
    }
    emit scoreChanged();
}

void GameLogic::updateScoreDrope(bool isDropDown)
{
    score+= isDropDown ? 4:2;
    emit scoreChanged();
}

void GameLogic::swapPoketPiece()
{
    if(!m_canSwap) return;
    if(m_poketPiece.type()==Empty){
        m_poketPiece=m_curPiece;
        m_curPiece = m_nextPieces.front();
        m_nextPieces.pop_front();
        m_nextPieces.push_back(Tetromino(static_cast<TetrominoType>((rand() % 7) + 1)));
    }else{
        std::swap(m_poketPiece,m_curPiece);
        m_x = WIDTH / 2 - 1;
        m_y = 0;
    }
    m_canSwap=false;
    emit pocketChanged();
}

std::vector<Tetromino> GameLogic::getNextPieces() const {
    return {m_nextPieces.begin(), m_nextPieces.end()};
}
