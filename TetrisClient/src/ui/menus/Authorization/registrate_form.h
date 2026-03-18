#ifndef REGISTRATE_FORM_H
#define REGISTRATE_FORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui { class AuthForm; }

class RegisterForm : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

    QString nickname() const;
    void setNickname(const QString& nickname);

signals:
    void authCompleted(const QString& nickname);
    void backClicked();
    void loginClicked();

private slots:
    void onLoginClicked();

private:
    Ui::AuthForm *ui;
};

#endif // REGISTRATE_FORM_H
