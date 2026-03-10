#include "menu_widget.h"
#include "setting_manager.h"
#include <QString>
#include <QStyle>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    settingsLayout = new QHBoxLayout();
    
    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(stackedWidget);

    this->setStyleSheet(
        "background-image:  "
        "url(:/background_main.png);"
        );
    mainMenuWidget = new QWidget(this);
    QVBoxLayout *mainMenuLayout = new QVBoxLayout(mainMenuWidget);
    mainMenuLayout->addLayout(settingsLayout);

    bestScoreTitle = new QLabel("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
    bestScoreTitle->setStyleSheet("font-size: 36px; font-weight: bold; margin-bottom: 10px; background: transparent;");
    bestScoreTitle->setAlignment(Qt::AlignCenter);

    totalLinesTitle = new QLabel("ЛИНИИ: " + QString::number(SettingsManager::instance().totalyCoutLines()));
    totalLinesTitle->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px; color: #aaaaaa; background: transparent;");
    totalLinesTitle->setAlignment(Qt::AlignCenter);

    nicknameLabel = new QLabel();
    QString nickname = SettingsManager::instance().nickname();
    if (!nickname.isEmpty()) {
        nicknameLabel->setText(nickname);
        nicknameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #4CAF50; background: transparent;");
    } else {
        nicknameLabel->setText("Гость");
        nicknameLabel->setStyleSheet("font-size: 18px; color: #888888; background: transparent;");
    }
    nicknameLabel->setAlignment(Qt::AlignCenter);

    title = new QLabel("QT TETRIS");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px; background: transparent;");
    title->setAlignment(Qt::AlignCenter);

    btnStart = new QPushButton("ИГРАТЬ");
    btnExit = new QPushButton("ВЫХОД");

    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    mainMenuLayout->addWidget(title);
    mainMenuLayout->addWidget(nicknameLabel);
    mainMenuLayout->addStretch();
    mainMenuLayout->addWidget(bestScoreTitle);
    mainMenuLayout->addWidget(totalLinesTitle);
    mainMenuLayout->addWidget(btnStart);
    mainMenuLayout->addWidget(btnExit);
    mainMenuLayout->addStretch();

    connect(btnStart, &QPushButton::clicked, this, &MenuWidget::onStartClicked);
    connect(btnExit, &QPushButton::clicked, this, &MenuWidget::onExitClicked);

    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateBestScore);
    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateTotalLines);


    btnSettings = new QPushButton();
    btnUser = new QPushButton();
    btnStatistic = new QPushButton();
    QIcon settingsIcon(":/settings_icon.svg");
    QIcon userIcon(":/user_icon.svg");
    QIcon statisticIcon(":/statistic_icon.svg");

    btnSettings->setIcon(settingsIcon);
    btnUser->setIcon(userIcon);
    btnStatistic->setIcon(statisticIcon);
    btnSettings->setStyleSheet(btnStyle);
    btnUser->setStyleSheet(btnStyle);
    btnStatistic->setStyleSheet(btnStyle);
    btnSettings->setFixedSize(40,40);
    btnUser->setFixedSize(40,40);
    btnStatistic->setFixedSize(40,40);
    settingsLayout->addWidget(btnSettings);
    settingsLayout->addWidget(btnUser);
    settingsLayout->addWidget(btnStatistic);
    settingsLayout->setAlignment(Qt::AlignTop);

    connect(btnUser, &QPushButton::clicked, this, &MenuWidget::onUserClicked);


    authFormWidget = new QWidget(this);
    QVBoxLayout *authLayout = new QVBoxLayout(authFormWidget);
    authForm = new AuthForm(this);
    authLayout->addWidget(authForm);

    connect(authForm, &AuthForm::authCompleted, this, &MenuWidget::onAuthDone);
    connect(authForm, &AuthForm::backClicked, this, &MenuWidget::onAuthBack);


    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(authFormWidget);
}

void MenuWidget::updateBestScore() {
    bestScoreTitle->setText("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
}

void MenuWidget::updateTotalLines() {
    totalLinesTitle->setText("ЛИНИИ: " + QString::number(SettingsManager::instance().totalyCoutLines()));
}

void MenuWidget::onUserClicked() {

    authForm->setNickname(SettingsManager::instance().nickname());
    stackedWidget->setCurrentWidget(authFormWidget);
    authForm->setFocus();
}

void MenuWidget::onAuthBack() {
    stackedWidget->setCurrentWidget(mainMenuWidget);
    mainMenuWidget->setFocus();
}

void MenuWidget::onAuthDone(const QString& nickname) {
    SettingsManager::instance().updateNickname(nickname);
    emit onAuthCompleted(nickname);
    

    if (!nickname.isEmpty()) {
        nicknameLabel->setText(nickname);
        nicknameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #4CAF50; background: transparent;");
    } else {
        nicknameLabel->setText("Гость");
        nicknameLabel->setStyleSheet("font-size: 18px; color: #888888; background: transparent;");
    }
    
    stackedWidget->setCurrentWidget(mainMenuWidget);
    mainMenuWidget->setFocus();
}
