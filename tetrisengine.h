#ifndef TETRISENGINE_H
#define TETRISENGINE_H

#include <QObject>

class TetrisEngine : public QObject
{
    Q_OBJECT
public:
    explicit TetrisEngine(QObject *parent = nullptr);

signals:
};

#endif // TETRISENGINE_H
