#include "fild_widget.h"
#include <QElapsedTimer>
FildWidget::FildWidget(QWidget *parent) : QWidget(parent) {
    CELL_SIZE=30;
    setFocusPolicy(Qt::StrongFocus);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FildWidget::gameStep);

    m_timer->start(50);

    setFixedSize((m_game.WIDTH * CELL_SIZE)+20, (m_game.HEIGHT * CELL_SIZE)+20);

    inputTimer = new QTimer(this);
    connect(inputTimer, &QTimer::timeout, this, &FildWidget::processInput);
    inputTimer->start(50);

    rotateTimer.start();

}

void FildWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setPen(QColor(40, 40, 40));
    painter.setBrush(Qt::NoBrush);

    for(int y = 0; y <= m_game.HEIGHT+1; ++y) {

        painter.drawLine(0, y * CELL_SIZE, m_game.WIDTH * CELL_SIZE, y * CELL_SIZE);
    }
    for(int x = 0; x <= m_game.WIDTH+1; ++x) {

        painter.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, m_game.HEIGHT * CELL_SIZE);
    }
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
void FildWidget::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        pressedKeys.insert(event->key());
    }

}

void FildWidget::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        pressedKeys.remove(event->key());
    }
}
void FildWidget::processInput() {
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
    if(pressedKeys.contains(Qt::Key_Shift)) m_game.swapPoketPiece();
    if (pressedKeys.contains(Qt::Key_Escape)){
        pressedKeys.clear();
        emit escapePressed();
        return;
    }
    update();
}

void FildWidget::gameStep() {
    m_game.moveDown();

    update();
}
