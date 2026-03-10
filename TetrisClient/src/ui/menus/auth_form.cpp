#include "auth_form.h"
#include "ui_auth_form.h"

AuthForm::AuthForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &AuthForm::onLoginClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &AuthForm::backClicked);
}

AuthForm::~AuthForm()
{
    delete ui;
}

QString AuthForm::nickname() const
{
    return ui->nicknameEdit->text();
}

void AuthForm::setNickname(const QString& nickname)
{
    ui->nicknameEdit->setText(nickname);
}

void AuthForm::onLoginClicked()
{
    emit authCompleted(ui->nicknameEdit->text());
}
