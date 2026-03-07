#include "overlay_widget.h"

OverlayWidget::OverlayWidget(QWidget *parent)
    : QWidget{parent}
{
    setupCommonStyle();
    setupLayout();
}

void OverlayWidget::setupCommonStyle() {
    setStyleSheet("background-color: rgba(0, 0, 0, 150);");
}

void OverlayWidget::setupLayout() {
    layout = new QVBoxLayout(this);
    
    title = new QLabel();
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px;");
    title->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(title);
}

QPushButton* OverlayWidget::createButton(const QString &text) {
    QPushButton *button = new QPushButton(text);
    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    button->setStyleSheet(btnStyle);
    return button;
}

void OverlayWidget::addStretchTop() {
    layout->insertStretch(0);
}

void OverlayWidget::addStretchBottom() {
    layout->addStretch();
}
