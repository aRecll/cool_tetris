#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>


class QStackedWidget;
class QLabel;
class AuthForm;
class SettingWidget;
class StatisticWidget;

class MenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void onStartClicked();
    void onExitClicked();
    void onAuthCompleted(const QString& nickname);

private slots:
    void updateBestScore();
    void updateTotalLines();
    void onUserClicked();
    void onSettingsClicked();
    void onSettingsBack();
    void onStatisticClicked();
    void onStatisticBack();
   // void onStatistikClicked();
    void onAuthBack();

    void onAuthDone(const QString& nickname);

private:

    void setupUi();
    QWidget* createMainMenu();
    QWidget* createAuthFormPage();
    QWidget* createSettingsPage();
    QWidget* createStatisticPage();
    void updateNicknameUI(const QString& nickname);


    QStackedWidget *m_stackedWidget = nullptr;
    QLabel *m_bestScoreTitle = nullptr;
    QLabel *m_totalLinesTitle = nullptr;
    QLabel *m_nicknameLabel = nullptr;
    AuthForm *m_authForm = nullptr;
    SettingWidget *m_settingWidget = nullptr;
    StatisticWidget *m_statisticWidget = nullptr;
};

#endif // MENU_WIDGET_H
