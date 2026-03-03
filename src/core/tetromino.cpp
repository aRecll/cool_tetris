#include "tetromino.h"

Tetromino::Tetromino(TetrominoType type) : m_type(type) {
    switch (type) {
    case I: m_coords = {{0, -1}, {0, 0}, {0, 1}, {0, 2}}; break;
    case J: m_coords = {{0, -1}, {0, 0}, {0, 1}, {-1, 1}}; break;
    case L: m_coords = {{0, -1}, {0, 0}, {0, 1}, {1, 1}}; break;
    case O: m_coords = {{0, 0}, {1, 0}, {0, 1}, {1, 1}}; break;
    case S: m_coords = {{0, 0}, {1, 0}, {0, 1}, {-1, 1}}; break;
    case T: m_coords = {{-1, 0}, {0, 0}, {1, 0}, {0, 1}}; break;
    case Z: m_coords = {{0, 0}, {-1, 0}, {0, 1}, {1, 1}}; break;
    default: m_coords = {}; break;
    }
}

void Tetromino::rotate() {
    if (m_type == O) return;
    for (auto &p : m_coords) {
        int temp = p.x;
        p.x = -p.y;
        p.y = temp;
    }
}

std::vector<Point> Tetromino::getPoints(int offsetX, int offsetY) const {
    std::vector<Point> absolute;
    for (const auto &p : m_coords) {
        absolute.push_back({p.x + offsetX, p.y + offsetY});
    }
    return absolute;
}



QColor Tetromino::color() const {
    switch (m_type) {
    case I: return Qt::cyan;
    case J: return Qt::blue;
    case L: return QColor(255, 165, 0);
    case O: return Qt::yellow;
    case S: return Qt::green;
    case T: return QColor(128, 0, 128);
    case Z: return Qt::red;
    default: return Qt::transparent;
    }
}
QColor Tetromino::getColorForType(int type) {
    switch (static_cast<TetrominoType>(type)) {
    case I: return Qt::cyan;
    case J: return Qt::blue;
    case L: return QColor(255, 165, 0);
    case O: return Qt::yellow;
    case S: return Qt::green;
    case T: return QColor(128, 0, 128);
    case Z: return Qt::red;
    default: return Qt::transparent;
    }
}
