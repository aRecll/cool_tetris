#ifndef OVERLAY_WIDGET_H
#define OVERLAY_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class OverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OverlayWidget(QWidget *parent = nullptr);
    
protected:
    QVBoxLayout *layout;
    QLabel *title;
    
    void setupLayout();
    QPushButton* createButton(const QString &text);
    void addStretchTop();
    void addStretchBottom();
    
private:
    void setupCommonStyle();
};

#endif // OVERLAY_WIDGET_H
