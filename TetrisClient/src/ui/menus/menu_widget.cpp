#include "menu_widget.h"
#include "setting_manager.h"
#include "registrate_form.h"
#include "setting_widget.h"
#include "statistic_widget.h"
#include "user_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QIcon>

MenuWidget::MenuWidget(QWidget *parent) : QWidget{parent} {
    setupUi();

    this->setStyleSheet(

        "background-image:  "

        "url(:/background_main.png);"

        );
    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateBestScore);
    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateTotalLines);
}

void MenuWidget::setupUi() {
    auto *layout = new QVBoxLayout(this);
    m_stackedWidget = new QStackedWidget(this);
    layout->addWidget(m_stackedWidget);

    setStyleSheet("MenuWidget { background-image: url(:/background_main.png); }");

    m_stackedWidget->addWidget(createMainMenu());
    m_stackedWidget->addWidget(createUserWidget());
    // m_stackedWidget->addWidget(createAuthFormPage());
    m_stackedWidget->addWidget(createSettingsPage());
    m_stackedWidget->addWidget(createStatisticPage());
}

QWidget* MenuWidget::createMainMenu() {
    auto *page = new QWidget(this);
    auto *mainMenuLayout = new QVBoxLayout(page);
    auto *settingsLayout = new QHBoxLayout();

    mainMenuLayout->addLayout(settingsLayout);


    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    //////////;)
    auto createSmallBtn = [&](const QString& iconPath) {
        auto *btn = new QPushButton(QIcon(iconPath), "");
        btn->setFixedSize(40, 40);
        btn->setStyleSheet(btnStyle);
        settingsLayout->addWidget(btn);
        return btn;
    };

    auto *btnSettings = createSmallBtn(":/settings_icon.svg");
    auto *btnUser     = createSmallBtn(":/user_icon.svg");
    auto *btnStatistic = createSmallBtn(":/statistic_icon.svg");
    settingsLayout->setAlignment(Qt::AlignTop);


    auto *title = new QLabel("QT TETRIS");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px; background: transparent;");
    title->setAlignment(Qt::AlignCenter);

    m_nicknameLabel = new QLabel();
    m_nicknameLabel->setAlignment(Qt::AlignCenter);
    updateNicknameUI(SettingsManager::instance().nickname());

    m_bestScoreTitle = new QLabel();
    m_bestScoreTitle->setStyleSheet("font-size: 36px; font-weight: bold; margin-bottom: 10px; background: transparent;");
    m_bestScoreTitle->setAlignment(Qt::AlignCenter);
    updateBestScore();

    m_totalLinesTitle = new QLabel();
    m_totalLinesTitle->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px; color: #aaaaaa; background: transparent;");
    m_totalLinesTitle->setAlignment(Qt::AlignCenter);
    updateTotalLines();


    auto *btnStart = new QPushButton("PLAY");
    auto *btnExit = new QPushButton("EXIT");
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    mainMenuLayout->addWidget(title);
    mainMenuLayout->addWidget(m_nicknameLabel);
    mainMenuLayout->addStretch();
    mainMenuLayout->addWidget(m_bestScoreTitle);
    mainMenuLayout->addWidget(m_totalLinesTitle);
    mainMenuLayout->addWidget(btnStart);
    mainMenuLayout->addWidget(btnExit);
    mainMenuLayout->addStretch();


    connect(btnStart, &QPushButton::clicked, this, &MenuWidget::onStartClicked);
    connect(btnExit, &QPushButton::clicked, this, &MenuWidget::onExitClicked);
    connect(btnUser, &QPushButton::clicked, this, &MenuWidget::onUserClicked);
    connect(btnSettings, &QPushButton::clicked, this, &MenuWidget::onSettingsClicked);
    connect(btnStatistic, &QPushButton::clicked, this, &MenuWidget::onStatisticClicked);

    return page;
}

QWidget *MenuWidget::createUserWidget()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    m_userWidget = new UserWidget(this);
    layout->addWidget(m_userWidget);

    connect(m_userWidget,&UserWidget::backInMainMenuClicked,this,&MenuWidget::onUserBack);
    return page;
}

// QWidget* MenuWidget::createAuthFormPage() {
//     auto *page = new QWidget(this);
//     auto *layout = new QVBoxLayout(page);
//     m_userWidget = new RegisterForm(this);
//     layout->addWidget(m_authForm);

//     connect(m_authForm, &RegisterForm::authCompleted, this, &MenuWidget::onAuthDone);
//     connect(m_authForm, &RegisterForm::backClicked, this, &MenuWidget::onAuthBack);
//     return page;
// }

QWidget* MenuWidget::createSettingsPage() {
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    m_settingWidget = new SettingWidget(this);
    layout->addWidget(m_settingWidget);

    connect(m_settingWidget, &SettingWidget::backClicked, this, &MenuWidget::onSettingsBack);

    return page;
}

QWidget* MenuWidget::createStatisticPage() {
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);
    m_statisticWidget = new StatisticWidget(this);
    layout->addWidget(m_statisticWidget);

    connect(m_statisticWidget, &StatisticWidget::backClicked, this, &MenuWidget::onStatisticBack);

    return page;
}



void MenuWidget::updateBestScore() {
    m_bestScoreTitle->setText("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
}

void MenuWidget::updateTotalLines() {
    m_totalLinesTitle->setText("LINES: " + QString::number(SettingsManager::instance().totalyCoutLines()));
}

void MenuWidget::updateNicknameUI(const QString& nickname) {
    if (!nickname.isEmpty()) {
        m_nicknameLabel->setText(nickname);
        m_nicknameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #4CAF50; background: transparent;");
    } else {
        m_nicknameLabel->setText("GUEST");
        m_nicknameLabel->setStyleSheet("font-size: 18px; color: #888888; background: transparent;");
    }
}

void MenuWidget::onUserClicked() {
   // m_authForm->setNickname(SettingsManager::instance().nickname());
    m_stackedWidget->setCurrentIndex(1);
   // m_authForm->setFocus();
}

void MenuWidget::onUserBack()
{
m_stackedWidget->setCurrentIndex(0);
}

void MenuWidget::onSettingsClicked() {
    m_stackedWidget->setCurrentIndex(2);
}

void MenuWidget::onSettingsBack() {
    m_stackedWidget->setCurrentIndex(0);
}

void MenuWidget::onStatisticClicked() {
    m_statisticWidget->updateStatistics();
    m_stackedWidget->setCurrentIndex(3);
}

void MenuWidget::onStatisticBack() {
    m_stackedWidget->setCurrentIndex(0);
}

// void MenuWidget::onAuthBack() {
//     m_stackedWidget->setCurrentIndex(0);
// }

// void MenuWidget::onAuthDone(const QString& nickname) {
//     SettingsManager::instance().updateNickname(nickname);
//     updateNicknameUI(nickname);
//     emit onAuthCompleted(nickname);
//     onAuthBack();
// }
