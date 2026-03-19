#include "login_form.h"
#include "ui_login_form.h"
#include "network_managerv2.h"
#include "setting_manager.h"
LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_form)
{
    ui->setupUi(this);
   // ui->label->hide();
     connect(ui->backButton, &QPushButton::clicked, this, &LoginForm::backInAuthFormClicked);
    connect(ui->RegistrateButton, &QPushButton::clicked, this, &LoginForm::onLoginClicked);
    connect(&NetworkManagerV2::instance(),&NetworkManagerV2::loginSuccess,this,&LoginForm::onLoginSuccess);
    connect(&NetworkManagerV2::instance(),&NetworkManagerV2::loginFailed,this,&LoginForm::onLoginFailed);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::onLoginClicked()
{
    NetworkManagerV2::instance().loginInAccount(getNickname(),getPassword());



}

void LoginForm::onLoginFailed(QString err)
{
    qDebug() <<err;
    ui->label_2->setText("NOOOOT GOOD");
    ui->label_2->show();
}

void LoginForm::onLoginSuccess()
{
    ui->label_2->setText("GOOD");
    ui->label_2->show();
}




QString LoginForm::getNickname() const
{
    return ui->nicknameEdit->text();
}

QString LoginForm::getPassword() const
{
    return ui->PassEdit->text();
}
