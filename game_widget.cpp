#include "game_widget.h"
#include <QElapsedTimer>
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWidget::gameStep);

    m_timer->start(500);
    setFixedSize(m_game.WIDTH * CELL_SIZE, m_game.HEIGHT * CELL_SIZE);

    inputTimer = new QTimer(this);
    connect(inputTimer, &QTimer::timeout, this, &GameWidget::processInput);
    inputTimer->start(50);

    rotateTimer.start();

}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);


    for(int y = 0; y < m_game.HEIGHT; ++y) {
        for(int x = 0; x < m_game.WIDTH; ++x) {
            int typeIndex = m_game.getCell(x, y);
            if(typeIndex > 0) {


                painter.fillRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, Tetromino::getColorForType(typeIndex));


                painter.setPen( Tetromino::getColorForType(typeIndex).darker());
                painter.drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1);
            }
        }
    }


    painter.setBrush(m_game.curPiece().color());
    painter.setPen(m_game.curPiece().color().darker());
    for(auto p : m_game.curPiece().getPoints(m_game.curPos().x, m_game.curPos().y)) {
        painter.drawRect(p.x * CELL_SIZE, p.y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1);
    }
}
void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        pressedKeys.insert(event->key());
    }

}

void GameWidget::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        pressedKeys.remove(event->key());
    }
}
void GameWidget::processInput() {
    if (pressedKeys.contains(Qt::Key_Left))  m_game.moveLeft();
    if (pressedKeys.contains(Qt::Key_Right)) m_game.moveRight();
    if (pressedKeys.contains(Qt::Key_Down))  m_game.moveDown();
    if (pressedKeys.contains(Qt::Key_Up)) {
        if (rotateTimer.elapsed() > ROTATE_COOLDOWN) {
            m_game.rotate();
            rotateTimer.restart();
        }
    }
    if(pressedKeys.contains(Qt::Key_Space)){
        if (rotateTimer.elapsed() > ROTATE_COOLDOWN) {
            m_game.instaMoveDown();
            rotateTimer.restart();
        }


    }
    if (pressedKeys.contains(Qt::Key_Escape)) emit escapePressed();

    update();
}

void GameWidget::gameStep() {
    m_game.moveDown();
    update();
}
