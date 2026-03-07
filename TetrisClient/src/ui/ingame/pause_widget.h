#ifndef PAUSE_WIDGET_H
#define PAUSE_WIDGET_H

#include "overlay_widget.h"
#include <QPushButton>

class PauseWidget : public OverlayWidget
{
    Q_OBJECT
public:
    explicit PauseWidget(QWidget *parent = nullptr);
signals:
    void backInGame();
    void startNewGame();
    void onExitClicked();
private:
    QPushButton *btnStart;
    QPushButton *btnExit;
    QPushButton *btnNewGame;
};

#endif // PAUSE_WIDGET_H
