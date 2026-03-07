#ifndef GAME_OVER_WIDGET_H
#define GAME_OVER_WIDGET_H

#include "overlay_widget.h"
#include <QPushButton>
#include <QLabel>

class GameOverWidget : public OverlayWidget
{
    Q_OBJECT
public:
    explicit GameOverWidget(QWidget *parent = nullptr);
    
    void setFinalScore(int score);
    
signals:
    void startNewGame();
    void onExitClicked();
    
private:
    QPushButton *btnNewGame;
    QPushButton *btnExit;
    QLabel *scoreLabel;
};

#endif // GAME_OVER_WIDGET_H
