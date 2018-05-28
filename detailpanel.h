#pragma once

#include <QWidget>

class QStackedWidget;

class DetailPanel : public QWidget
{
    Q_OBJECT
public:
    explicit DetailPanel(QWidget *tree, QWidget *text);

private slots:
    void switchTabs(int index);

private:
    QStackedWidget *m_stackedWidget;

};





