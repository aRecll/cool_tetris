#include "statistic_widget.h"
#include "setting_manager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

StatisticWidget::StatisticWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    setupScrollArea();
    updateStatistics();
}

void StatisticWidget::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(15);

    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";

    m_titleLabel = new QLabel("STATISTICS", this);
    m_titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; background: transparent;");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addStretch();

    m_backButton = new QPushButton("Back", this);
    m_backButton->setStyleSheet(btnStyle);

    m_mainLayout->addWidget(m_backButton);

    connect(m_backButton, &QPushButton::clicked, this, &StatisticWidget::backClicked);
}

void StatisticWidget::setupScrollArea()
{
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setMinimumHeight(300);
    m_scrollArea->setMaximumWidth(600);

    QString scrollStyle = R"(
        QScrollArea {
            background-color: #2c3e50;
            border: 2px solid #34495e;
            border-radius: 12px;
            padding: 10px;
        }
        QScrollBar:vertical {
            background-color: #1a252f;
            width: 14px;
            border-radius: 7px;
            margin: 2px;
        }
        QScrollBar::handle:vertical {
            background-color: #7f8c8d;
            border-radius: 7px;
            min-height: 40px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: #95a5a6;
        }
        QScrollBar::handle:vertical:pressed {
            background-color: #bdc3c7;
        }
        QScrollBar::add-line:vertical {
            height: 0px;
        }
        QScrollBar::sub-line:vertical {
            height: 0px;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: transparent;
        }
        QScrollBar:horizontal {
            background-color: #1a252f;
            height: 0px;
        }
    )";
    m_scrollArea->setStyleSheet(scrollStyle);

    m_statsContent = new QWidget();
    m_statsLayout = new QVBoxLayout(m_statsContent);
    m_statsLayout->setSpacing(10);
    m_statsLayout->setContentsMargins(15, 10, 20, 15);

    m_scrollArea->setWidget(m_statsContent);

    m_mainLayout->insertWidget(1, m_scrollArea);
}

void StatisticWidget::addStatRow(const QString& name, const QString& value)
{
    QHBoxLayout* itemLayout = new QHBoxLayout();
    itemLayout->setSpacing(10);
    itemLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* nameLabel = new QLabel(name, m_statsContent);
    nameLabel->setStyleSheet("QLabel { color: #bdc3c7; font-size: 15px; font-weight: normal; background: transparent; }");
    nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nameLabel->setMinimumWidth(200);

    QLabel* valueLabel = new QLabel(value, m_statsContent);
    valueLabel->setStyleSheet("QLabel { color: #f1c40f; font-size: 16px; font-weight: bold; background: transparent; }");
    valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    itemLayout->addWidget(nameLabel);
    itemLayout->addStretch();
    itemLayout->addWidget(valueLabel);

    m_statsLayout->addLayout(itemLayout);
    m_statLabels.append(nameLabel);
    m_statLabels.append(valueLabel);
}

QString StatisticWidget::formatTime(int seconds) const
{
    int hours = seconds / 3600;
    int mins = (seconds % 3600) / 60;
    int secs = seconds % 60;

    if (hours > 0) {
        return QString("%1h %2m %3s").arg(hours).arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0'));
    } else if (mins > 0) {
        return QString("%1m %2s").arg(mins).arg(secs, 2, 10, QChar('0'));
    }
    return QString("%1s").arg(secs);
}

void StatisticWidget::updateStatistics()
{
    for (QLabel* label : m_statLabels) {
        label->deleteLater();
    }
    m_statLabels.clear();

    auto& settings = SettingsManager::instance();

    addStatRow("Nickname:", settings.nickname());
    addStatRow("Best Score:", QString::number(settings.getMaxScore()));
    addStatRow("Total Lines:", QString::number(settings.totalyCoutLines()));
    addStatRow("Games Played:", QString::number(settings.getCountGames()));
    addStatRow("Average Score:", QString::number(settings.getAverageScore()));
    addStatRow("TETRIS (4 lines):", QString::number(settings.getTotalTETRISCleared()));
    addStatRow("Total Lines (all games):", QString::number(settings.getTotalLinesCleared()));
    addStatRow("Tetrominoes Placed:", QString::number(settings.getTotalTetrominoesPlaced()));
    addStatRow("Time Played:", formatTime(settings.getTotalGameTime()));
    addStatRow("Games with 4 lines:", QString::number(settings.getGamesWithMaxLineClear()));

    m_statsLayout->addStretch();
}
