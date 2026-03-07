#include "game_widget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{
    QStackedLayout* mainLayout = new QStackedLayout(this);
    mainLayout->setStackingMode(QStackedLayout::StackAll);

    pauseWidget = new PauseWidget(this);
    pauseWidget->hide();
    
    gameOverWidget = new GameOverWidget(this);
    gameOverWidget->hide();
    
    gameLayer = new QWidget(this);
    hLayout = new QHBoxLayout(gameLayer);

    lefVLayout = new QVBoxLayout();
    midVLayout = new QVBoxLayout();
    rightVLayout = new QVBoxLayout();

    fildWidget = new FildWidget(this);
    scoreWidget = new ScoreWidget(fildWidget->getLogic(), this);
    nextWidget = new NextPiecesWidget(fildWidget->getLogic(), this);
    poketPieceWodget = new PoketPieceWidget(fildWidget->getLogic(), this);

    lefVLayout->addWidget(poketPieceWodget, 0, Qt::AlignTop);
    midVLayout->addWidget(scoreWidget);
    midVLayout->addWidget(fildWidget);
    rightVLayout->addWidget(nextWidget, 0, Qt::AlignTop);

    hLayout->addLayout(lefVLayout);
    hLayout->addLayout(midVLayout);
    hLayout->addLayout(rightVLayout);

    mainLayout->addWidget(gameLayer);
    mainLayout->addWidget(pauseWidget);
    mainLayout->addWidget(gameOverWidget);
    pauseWidget->raise();


    connect(&fildWidget->getLogic(), &GameLogic::tick, fildWidget, &FildWidget::gameStep);
    connect(&fildWidget->getLogic(), &GameLogic::nextPiecesChanged, nextWidget, QOverload<>::of(&NextPiecesWidget::update));
    connect(&fildWidget->getLogic(), &GameLogic::pocketChanged, poketPieceWodget, QOverload<>::of(&PoketPieceWidget::update));
    connect(&fildWidget->getLogic(), &GameLogic::scoreChanged, scoreWidget, QOverload<>::of(&ScoreWidget::update));
    connect(&fildWidget->getLogic(), &GameLogic::gameEnd, this, &GameWidget::showGameOver);

    connect(pauseWidget, &PauseWidget::onExitClicked, this, &GameWidget::escapePressed);
    connect(pauseWidget, &PauseWidget::backInGame, this, &GameWidget::pauseOff);
    connect(pauseWidget, &PauseWidget::startNewGame, this, &GameWidget::restart);
    
    connect(gameOverWidget, &GameOverWidget::onExitClicked, this, &GameWidget::escapePressed);
    connect(gameOverWidget, &GameOverWidget::startNewGame, this, &GameWidget::restart);

    connect(fildWidget, &FildWidget::escapePressed, this, &GameWidget::pauseOn);
}

void GameWidget::setFocus(Qt::FocusReason reason) {
    fildWidget->setFocus(reason);
}

void GameWidget::pauseOn() {
    fildWidget->getLogic().pause();
    fildWidget->setInputTimerEnabled(false);
    pauseWidget->show();
    pauseWidget->raise();
    pauseWidget->setFocus();
}

void GameWidget::restart()
{
    fildWidget->restart();
    fildWidget->setInputTimerEnabled(true);
    pauseWidget->hide();
    gameOverWidget->hide();
}

void GameWidget::pauseOff() {
    fildWidget->getLogic().resume();
    fildWidget->setInputTimerEnabled(true);
    pauseWidget->hide();
    fildWidget->setFocus();
}

void GameWidget::showGameOver() {
    gameOverWidget->setFinalScore(fildWidget->getLogic().getScore());
    gameOverWidget->show();
    gameOverWidget->raise();
    gameOverWidget->setFocus();
}
