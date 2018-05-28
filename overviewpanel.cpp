#include <QTabBar>
#include <QStackedWidget>
#include <QBoxLayout>

#include "overviewpanel.h"


OverviewPanel::OverviewPanel(QWidget *compilationUnits, QWidget *headers)
{
    QTabBar *tabBar = new QTabBar(this);
    tabBar->addTab("Compilation Units");
    tabBar->addTab("Headers");

    QBoxLayout *layoutHor = new QBoxLayout(QBoxLayout::LeftToRight);
    layoutHor->addWidget(tabBar);
    layoutHor->addStretch();

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(compilationUnits);
    m_stackedWidget->addWidget(headers);
    QBoxLayout *layoutVert = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layoutVert->addLayout(layoutHor);
    layoutVert->addWidget(m_stackedWidget);
    connect(tabBar, &QTabBar::currentChanged, this, &OverviewPanel::switchTabs );
}

void OverviewPanel::switchTabs(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}
