#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QWidget>
#include "registrate_form.h"
#include "login_form.h"
#include <qstackedwidget.h>
class UserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserWidget(QWidget *parent = nullptr);

signals:
    void backInMainMenuClicked();

private slots:
  //  void onBackInMainMenu();
    void onBackInAuthForm();
    void onSwithOnLoginForm();


private:
    void setupUi();
    QWidget* createAuthForm();
    QWidget* createLogForm();


//UserProfile....
    RegisterForm* authForm;
    LoginForm* loginForm;
    QStackedWidget *m_stackedWidget = nullptr;
};

#endif // USER_WIDGET_H
