#ifndef TETROMINO_H
#define TETROMINO_H

#include <Qvector>
#include <QPoint>
#include <QColor>

enum TetrisShape { Empty, I, O, T, S, Z, J, L };

class Tetromino {
public:
    Tetromino();
    void setShape(TetrisShape shape);
    void rotateLeft();
    void rotateRight();

    // Возвращает относительные координаты 4-х блоков фигуры
    QPoint blockPos(int index) const;
    TetrisShape shape() const { return currentShape; }
    QColor color() const;

private:
    TetrisShape currentShape;
    QPoint coords[4]; // Массив координат четырех квадратиков
};

#endif // TETROMINO_H
