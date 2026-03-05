#ifndef PAUSE_WIDGET_H
#define PAUSE_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
class PauseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PauseWidget(QWidget *parent = nullptr);
signals:
    void backInGame();
    void onExitClicked();
private:

    QVBoxLayout *layout;
    QPushButton *btnStart;
    QPushButton *btnExit ;
    QLabel *title;
signals:
};

#endif // PAUSE_WIDGET_H
