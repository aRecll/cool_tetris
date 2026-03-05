#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include "fild_widget.h"
#include "next_pieces_widget.h"
#include "poket_piece_widget.h"
#include "score_widget.h"
#include "pause_widget.h"
#include <QStackedLayout>
class GameWidget : public QWidget
{
    Q_OBJECT
public:
     GameWidget(QWidget *parent = nullptr);

    QHBoxLayout *hLayout ;
     QVBoxLayout *lefVLayout;
    QVBoxLayout *midVLayout;
     QVBoxLayout *rightVLayout;

    FildWidget* fildWidget ;
    NextPiecesWidget *nextWidget ;
    PoketPieceWidget *poketPieceWodget;
    ScoreWidget *scoreWidget;
    QStackedWidget *stackedWidget;
    QWidget *gameLayer;
    PauseWidget* pauseWidget;



    void setFocus(Qt::FocusReason reason = Qt::OtherFocusReason);
private slots:
    void pauseOff();
    void pauseOn();

signals:
    void escapePressed();
};

#endif // GAME_WIDGET_H
