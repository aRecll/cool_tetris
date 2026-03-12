#include "pause_widget.h"

PauseWidget::PauseWidget(QWidget *parent)
    : OverlayWidget{parent}
{
    title->setText("PAUSE");
    
    addStretchTop();
    
    btnStart = createButton("CONTINUE");
    btnNewGame = createButton("PLAY AGAIN");
    btnExit = createButton("EXIT IN MAIN MENU");

    layout->addWidget(btnStart);
    layout->addWidget(btnNewGame);
    layout->addWidget(btnExit);
    
    addStretchBottom();
    layout->setAlignment(Qt::AlignCenter);

    connect(btnStart, &QPushButton::clicked, this, &PauseWidget::backInGame);
    connect(btnNewGame, &QPushButton::clicked, this, &PauseWidget::startNewGame);
    connect(btnExit, &QPushButton::clicked, this, &PauseWidget::onExitClicked);
}
