#include "game_over_widget.h"

GameOverWidget::GameOverWidget(QWidget *parent)
    : OverlayWidget{parent}
{
    title->setText("ИГРА ОКОНЧЕНА");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 10px; color: #ff4444;");
    
    scoreLabel = new QLabel("Счёт: 0");
    scoreLabel->setStyleSheet("font-size: 28px; color: #ffffff;");
    scoreLabel->setAlignment(Qt::AlignCenter);
    
    addStretchTop();
    
    layout->addWidget(scoreLabel);
    layout->addSpacing(20);
    
    btnNewGame = createButton("НАЧАТЬ ЗАНОВО");
    btnExit = createButton("ВЫЙТИ В ГЛАВНОЕ МЕНЮ");

    layout->addWidget(btnNewGame);
    layout->addWidget(btnExit);
    
    addStretchBottom();
    layout->setAlignment(Qt::AlignCenter);

    connect(btnNewGame, &QPushButton::clicked, this, &GameOverWidget::startNewGame);
    connect(btnExit, &QPushButton::clicked, this, &GameOverWidget::onExitClicked);
}

void GameOverWidget::setFinalScore(int score) {
    scoreLabel->setText(QString("Счёт: %1").arg(score));
}
