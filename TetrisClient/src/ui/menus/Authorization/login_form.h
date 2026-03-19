#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QWidget>

namespace Ui {
class login_form;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

    void setNickname(const QString& nickname);
signals:
    //void authCompleted(const QString& nickname);
    void backInAuthFormClicked();
public slots:
    void onLoginFailed(QString err);
    void onLoginSuccess();
private slots:
   // void onLoginClicked();
    void onLoginClicked();
  //  void onLoginFailed();
   // void onLoginSucsess();
private:
    QString getNickname() const;
    QString getPassword() const;
    Ui::login_form *ui;
};

#endif // LOGIN_FORM_H
