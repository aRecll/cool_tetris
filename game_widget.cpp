#include "game_widget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::gameStep);
    m_timer->start(500); // Скорость падения
    setFixedSize(m_game.WIDTH * CELL_SIZE, m_game.HEIGHT * CELL_SIZE);
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Рисуем зафиксированные блоки
    for(int y=0; y<m_game.HEIGHT; ++y) {
        for(int x=0; x<m_game.WIDTH; ++x) {
            if(m_game.getCell(x, y)) {
                painter.fillRect(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1, Qt::blue);
            }
        }
    }

    // Рисуем активную фигуру
    painter.setBrush(m_game.curPiece().color());
    for(auto p : m_game.curPiece().getPoints(m_game.curPos().x, m_game.curPos().y)) {
        painter.drawRect(p.x*CELL_SIZE, p.y*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1);
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Left:  m_game.moveLeft(); break;
    case Qt::Key_Right: m_game.moveRight(); break;
    case Qt::Key_Down:  m_game.moveDown(); break;
    case Qt::Key_Up:    m_game.rotate(); break;
    }
    update();
}

void GameWidget::gameStep() {
    m_game.moveDown();
    update();
}
