#ifndef STATISTIC_WIDGET_H
#define STATISTIC_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

class StatisticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticWidget(QWidget *parent = nullptr);
    void updateStatistics();

signals:
    void backClicked();

private:
    void setupUi();
    void setupScrollArea();
    void addStatRow(const QString& name, const QString& value);
    QString formatTime(int seconds) const;

    QLabel* m_titleLabel = nullptr;
    QPushButton* m_backButton = nullptr;
    QScrollArea* m_scrollArea = nullptr;
    QWidget* m_statsContent = nullptr;
    QVBoxLayout* m_statsLayout = nullptr;
    QVBoxLayout* m_mainLayout = nullptr;
    QList<QLabel*> m_statLabels;
};

#endif // STATISTIC_WIDGET_H
