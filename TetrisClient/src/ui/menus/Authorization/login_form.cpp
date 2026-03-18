#include "login_form.h"
#include "ui_login_form.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_form)
{
    ui->setupUi(this);
     connect(ui->backButton, &QPushButton::clicked, this, &LoginForm::backInAuthFormClicked);
}

LoginForm::~LoginForm()
{
    delete ui;
}
