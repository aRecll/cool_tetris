#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "fild_widget.h"
#include "next_pieces_widget.h"
#include "poket_piece_widget.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
     GameWidget(QWidget *parent = nullptr);

    QHBoxLayout *hLayout ;
    FildWidget* fildWidget ;
    NextPiecesWidget *nextWidget ;
    PoketPieceWidget *poketPieceWodget;




    void setFocus(Qt::FocusReason reason = Qt::OtherFocusReason);

signals:
    void escapePressed();
};

#endif // GAME_WIDGET_H
