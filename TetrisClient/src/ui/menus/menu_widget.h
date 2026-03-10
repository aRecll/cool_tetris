#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include "auth_form.h"

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void onStartClicked();
    void onExitClicked();
    void onAuthCompleted(const QString& nickname);
private slots:
    void updateBestScore();
    void updateTotalLines();
    void onUserClicked();
    void onAuthBack();
    void onAuthDone(const QString& nickname);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *settingsLayout;
    QStackedWidget *stackedWidget;

    QWidget *mainMenuWidget;
    QWidget *authFormWidget;

    ////////////////////
    QPushButton *btnStart;
    QPushButton *btnExit;
    QLabel *title;
    QLabel *bestScoreTitle;
    QLabel *totalLinesTitle;
    QLabel *nicknameLabel;
    ////////////////////

    AuthForm *authForm;

    ///////////////////////
    QPushButton *btnSettings;
    QPushButton *btnUser;
    QPushButton *btnStatistic;
    ///////////////////////
};

#endif // MENU_WIDGET_H
