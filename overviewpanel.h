#ifndef OVERVIEWPANEL_H
#define OVERVIEWPANEL_H

#include <QWidget>


class QStackedWidget;

class OverviewPanel : public QWidget
{
    Q_OBJECT
public:
    OverviewPanel(QWidget *compilationUnits, QWidget *headers);

private slots:
    void switchTabs(int index);

private:
    QStackedWidget *m_stackedWidget;
};

#endif // OVERVIEWPANEL_H
