#include "pause_widget.h"

PauseWidget::PauseWidget(QWidget *parent)
    : QWidget{parent}
{
    setStyleSheet("background-color: rgba(0, 0, 0, 150);");
    layout = new QVBoxLayout(this);
    title = new QLabel("ПАУЗА");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px;");
    title->setAlignment(Qt::AlignCenter);

    btnStart = new QPushButton("ПРОДОЛЖИТЬ");
    btnExit = new QPushButton("ВЫЙТИ В ГЛАВНОЕ МЕНЮ");


    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(btnStart);
    layout->addWidget(btnExit);
    layout->addStretch();
    layout->setAlignment(Qt::AlignCenter);


    connect(btnStart, &QPushButton::clicked, this, &PauseWidget::backInGame);
    connect(btnExit, &QPushButton::clicked, this, &PauseWidget::onExitClicked);


}
