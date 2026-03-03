#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <QColor>

enum TetrominoType { Empty = 0, I, J, L, O, S, T, Z };

struct Point { int x, y; };

class Tetromino {
public:
    Tetromino(TetrominoType type = Empty);
    void rotate();
    std::vector<Point> getPoints(int offsetX = 0, int offsetY = 0) const;
    void setPoints(int offsetX = 0, int offsetY = 0);
    TetrominoType type() const { return m_type; }
    QColor color() const;
    static QColor getColorForType(int type);

private:
    TetrominoType m_type;
    std::vector<Point> m_coords;
};

#endif
