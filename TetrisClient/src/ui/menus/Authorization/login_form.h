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
    QString nickname() const;
    void setNickname(const QString& nickname);
signals:
    //void authCompleted(const QString& nickname);
    void backInAuthFormClicked();
private slots:
   // void onLoginClicked();
private:
    Ui::login_form *ui;
};

#endif // LOGIN_FORM_H
