#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);

signals:
    void backClicked();

private:
    void setupUi();

    QLabel* m_titleLabel = nullptr;
    QPushButton* m_backButton = nullptr;
};

#endif // SETTING_WIDGET_H
