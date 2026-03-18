#include "user_widget.h"

UserWidget::UserWidget(QWidget *parent)
    : QWidget{parent}
{
    setupUi();


}

void UserWidget::onBackInAuthForm()
{
    m_stackedWidget->setCurrentIndex(0);
}

void UserWidget::onSwithOnLoginForm()
{
    m_stackedWidget->setCurrentIndex(1);
}

void UserWidget::setupUi()
{
    auto *layout = new QVBoxLayout(this);
    m_stackedWidget = new QStackedWidget(this);
    layout->addWidget(m_stackedWidget);

    //setStyleSheet("MenuWidget { background-image: url(:/background_main.png); }");
    m_stackedWidget->addWidget(createAuthForm());
    m_stackedWidget->addWidget(createLogForm());

    connect(loginForm,&LoginForm::backInAuthFormClicked,this,&UserWidget::onBackInAuthForm);
    connect(authForm,&RegisterForm::loginClicked,this,&UserWidget::onSwithOnLoginForm);
    connect(authForm,&RegisterForm::backClicked,this,&UserWidget::backInMainMenuClicked);
}

QWidget* UserWidget::createAuthForm()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    authForm = new RegisterForm(this);
    layout->addWidget(authForm);
    return page;
}

QWidget* UserWidget::createLogForm()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    loginForm = new LoginForm(this);
    layout->addWidget(loginForm);
    return page;
}
