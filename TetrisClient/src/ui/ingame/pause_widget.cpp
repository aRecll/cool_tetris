#include "pause_widget.h"

PauseWidget::PauseWidget(QWidget *parent)
    : OverlayWidget{parent}
{
    title->setText("ПАУЗА");
    
    addStretchTop();
    
    btnStart = createButton("ПРОДОЛЖИТЬ");
    btnNewGame = createButton("НАЧАТЬ ЗАНОВО");
    btnExit = createButton("ВЫЙТИ В ГЛАВНОЕ МЕНЮ");

    layout->addWidget(btnStart);
    layout->addWidget(btnNewGame);
    layout->addWidget(btnExit);
    
    addStretchBottom();
    layout->setAlignment(Qt::AlignCenter);

    connect(btnStart, &QPushButton::clicked, this, &PauseWidget::backInGame);
    connect(btnNewGame, &QPushButton::clicked, this, &PauseWidget::startNewGame);
    connect(btnExit, &QPushButton::clicked, this, &PauseWidget::onExitClicked);
}
