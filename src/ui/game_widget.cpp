#include "game_widget.h"



GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{

    hLayout = new QHBoxLayout(this);
    fildWidget = new FildWidget (this);
    nextWidget = new NextPiecesWidget(fildWidget->getLogic(), this);
    poketPieceWodget= new PoketPieceWidget(fildWidget->getLogic(), this);
    hLayout->addWidget(poketPieceWodget, 0, Qt::AlignTop);
    hLayout->addWidget(fildWidget);
    hLayout->addWidget(nextWidget, 0, Qt::AlignTop);


connect(&fildWidget->getLogic(), &GameLogic::nextPiecesChanged, nextWidget, QOverload<>::of(&NextPiecesWidget::update));
connect(&fildWidget->getLogic(), &GameLogic::pocketChanged, poketPieceWodget, QOverload<>::of(&PoketPieceWidget::update));

connect(fildWidget, &FildWidget::escapePressed, this, &GameWidget::escapePressed);



}
void GameWidget::setFocus(Qt::FocusReason reason) {

    fildWidget->setFocus(reason);
}
