#include "setting_manager.h"

SettingsManager::SettingsManager(QObject *parent) 
    : QObject{parent}
    , m_MaxScore(0)
    , m_totalyCoutLines(0)
    , m_nickname("гость")
    , m_countGames(0)
    , m_totalTETRISCleared(0)
    , m_totalTetrominoesPlaced(0)
    , m_totalGameTime(0)
    , m_gamesWithMaxLineClear(0)
{
    m_settings = new QSettings(this);
    initDefaultControls();
}

void SettingsManager::initDefaultControls()
{
    m_controls = {
        {MoveLeft, QKeySequence(Qt::Key_Left)},
        {MoveRight, QKeySequence(Qt::Key_Right)},
        {Rotate, QKeySequence(Qt::Key_Up)},
        {MoveDown, QKeySequence(Qt::Key_Down)},
        {Drop, QKeySequence(Qt::Key_Space)},
        {Pause, QKeySequence(Qt::Key_P)}
    };
}

// int SettingsManager::getCountGames() const
// {
//     return m_countGames;
// }

void SettingsManager::updateCountGames()
{
    m_countGames++;
    emit statisticsChanged();
}

bool SettingsManager::updateMaxScore(int score)
{
    if (score > m_MaxScore) {
        m_MaxScore = score;
        emit scoresChanged();
        return true;
    }
    return false;
}

SettingsManager& SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

void SettingsManager::loadSettings()
{

    m_nickname = m_settings->value("player/name", "Игрок").toString();
    m_MaxScore = m_settings->value("game/bestScore", 0).toInt();
    m_totalyCoutLines = m_settings->value("game/totalyCoutLines", 0).toInt();
    

    m_countGames = m_settings->value("stats/countGames", 0).toInt();
    m_totalTETRISCleared = m_settings->value("stats/totalLinesCleared", 0).toInt();
    m_totalTetrominoesPlaced = m_settings->value("stats/totalTetrominoesPlaced", 0).toInt();
    m_totalGameTime = m_settings->value("stats/totalGameTime", 0).toInt();
    m_gamesWithMaxLineClear = m_settings->value("stats/gamesWithMaxLineClear", 0).toInt();
    

    for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
        QString keyName = QString::number(it.key());
        QString defaultVal = it.value().toString();
        QString savedVal = m_settings->value("controls/" + keyName, defaultVal).toString();
        it.value() = QKeySequence(savedVal);
    }
    
    emit settingsReaded();
}

void SettingsManager::saveSettings()
{

    m_settings->setValue("player/name", m_nickname);
    m_settings->setValue("game/bestScore", m_MaxScore);
    m_settings->setValue("game/totalyCoutLines", m_totalyCoutLines);
    

    m_settings->setValue("stats/countGames", m_countGames);
    m_settings->setValue("stats/totalLinesCleared", m_totalTETRISCleared);
    m_settings->setValue("stats/totalTetrominoesPlaced", m_totalTetrominoesPlaced);
    m_settings->setValue("stats/totalGameTime", m_totalGameTime);
    m_settings->setValue("stats/gamesWithMaxLineClear", m_gamesWithMaxLineClear);
    

    for (auto it = m_controls.begin(); it != m_controls.end(); ++it) {
        m_settings->setValue("controls/" + QString::number(it.key()), it.value().toString());
    }
    
    m_settings->sync();
}

// int SettingsManager::totalyCoutLines() const
// {
//     return m_totalyCoutLines;
// }

void SettingsManager::updateTotalyCoutLines(int oneGameTotalyCoutLines)
{
    m_totalyCoutLines += oneGameTotalyCoutLines;
    emit scoresChanged();
}

// QString SettingsManager::nickname() const
// {
//     return m_nickname;
// }

void SettingsManager::updateNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}



void SettingsManager::updateTotalTETRISCleared(int lines)
{
    m_totalTETRISCleared += lines;
    if (lines == 4) {
        updateGamesWithMaxLineClear();
    }
    emit statisticsChanged();
}

void SettingsManager::updateTotalTetrominoesPlaced(int count)
{
    m_totalTetrominoesPlaced += count;
    emit statisticsChanged();
}

void SettingsManager::updateTotalGameTime(int seconds)
{
    m_totalGameTime += seconds;
    emit statisticsChanged();
}

int SettingsManager::getAverageScore() const
{
    if (m_countGames == 0) return 0;
    return m_MaxScore / m_countGames;
}
void SettingsManager::updateGamesWithMaxLineClear()
{
    m_gamesWithMaxLineClear++;
    emit statisticsChanged();
}



QKeySequence SettingsManager::getControl(ControlAction action) const
{
    return m_controls.value(action, QKeySequence());
}

void SettingsManager::setControl(ControlAction action, const QKeySequence& key)
{
    m_controls[action] = key;
    emit controlsChanged();
}

QMap<SettingsManager::ControlAction, QKeySequence> SettingsManager::getAllControls() const
{
    return m_controls;
}

void SettingsManager::setAllControls(const QMap<ControlAction, QKeySequence>& controls)
{
    m_controls = controls;
    emit controlsChanged();
}

void SettingsManager::resetControlsToDefault()
{
    initDefaultControls();
    emit controlsChanged();
}

QString SettingsManager::getControlActionName(ControlAction action) const
{
    switch (action) {
        case MoveLeft: return "Move Left";
        case MoveRight: return "Move Right";
        case Rotate: return "Rotate";
        case MoveDown: return "Move Down";
        case Drop: return "Drop";
        case Pause: return "Pause";
        default: return "Unknown";
    }
}
