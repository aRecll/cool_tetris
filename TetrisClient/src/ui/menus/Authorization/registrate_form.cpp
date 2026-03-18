#include "registrate_form.h"
#include "ui_registrate_form.h"

RegisterForm::RegisterForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);

   // connect(ui->loginButton, &QPushButton::clicked, this, &RegisterForm::onLoginClicked);
    connect(ui->loginButton, &QPushButton::clicked, this, &RegisterForm::loginClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &RegisterForm::backClicked);
  //  connect(ui->re, &QPushButton::clicked, this, &RegisterForm::backClicked);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

QString RegisterForm::nickname() const
{
    return ui->nicknameEdit->text();
}

void RegisterForm::setNickname(const QString& nickname)
{
    ui->nicknameEdit->setText(nickname);
}

void RegisterForm::onLoginClicked()
{
   // emit authCompleted(ui->nicknameEdit->text());
}
