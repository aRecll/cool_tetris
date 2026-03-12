#ifndef SETTING_MANAGER_H
#define SETTING_MANAGER_H

#include <QObject>
#include <QSettings>
#include <QMap>
#include <QKeySequence>
#include <QDateTime>

class SettingsManager: public QObject
{
    Q_OBJECT
public:
    enum ControlAction {
        MoveLeft,
        MoveRight,
        Rotate,
        MoveDown,
        Drop,
        Pause
    };
    
    static SettingsManager& instance();
    

    int getMaxScore() const { return m_MaxScore; }
    bool updateMaxScore(int score);
    
    int totalyCoutLines() const { return m_totalyCoutLines; }
    void updateTotalyCoutLines(int oneGameTotalyCoutLines);
    
    int getCountGames() const { return m_countGames; }
    void updateCountGames();
    

    int getTotalTETRISCleared() const { return m_totalTETRISCleared; }
    void updateTotalTETRISCleared(int lines);
    
    int getTotalTetrominoesPlaced() const { return m_totalTetrominoesPlaced; }
    void updateTotalTetrominoesPlaced(int count);
    
    int getTotalGameTime() const { return m_totalGameTime; }
    void updateTotalGameTime(int seconds);
    
    int getAverageScore() const;

    int getGamesWithMaxLineClear() const { return m_gamesWithMaxLineClear; }
    void updateGamesWithMaxLineClear();

    int getTotalLinesCleared() const { return m_totalLinesCleared; }

    QString nickname() const { return m_nickname; }
    void updateNickname(const QString &newNickname);
    

    QKeySequence getControl(ControlAction action) const;
    void setControl(ControlAction action, const QKeySequence& key);
    QMap<ControlAction, QKeySequence> getAllControls() const;
    void setAllControls(const QMap<ControlAction, QKeySequence>& controls);
    void resetControlsToDefault();
    QString getControlActionName(ControlAction action) const;
    

    void loadSettings();
    void saveSettings();

signals:
    void settingsReaded();
    void scoresChanged();
    void controlsChanged();
    void statisticsChanged();

private:
    explicit SettingsManager(QObject *parent = nullptr);
    
    QSettings* m_settings;
    

    int m_MaxScore;
    int m_totalyCoutLines;
    int m_countGames;
    int m_totalTETRISCleared;
    int m_totalLinesCleared;
    int m_totalTetrominoesPlaced;
    int m_totalGameTime;
    int m_gamesWithMaxLineClear;
    
    QString m_nickname;
    

    QMap<ControlAction, QKeySequence> m_controls;
    

    void initDefaultControls();
};

#endif // SETTING_MANAGER_H
