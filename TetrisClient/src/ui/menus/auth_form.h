#ifndef AUTH_FORM_H
#define AUTH_FORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui { class AuthForm; }

class AuthForm : public QWidget
{
    Q_OBJECT
public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

    QString nickname() const;
    void setNickname(const QString& nickname);

signals:
    void authCompleted(const QString& nickname);
    void backClicked();

private slots:
    void onLoginClicked();

private:
    Ui::AuthForm *ui;
};

#endif // AUTH_FORM_H
