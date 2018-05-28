#include <QTabBar>
#include <QBoxLayout>
#include <QStackedWidget>
#include "detailpanel.h"

DetailPanel::DetailPanel(QWidget *tree, QWidget *text)

{
    QTabBar *tabBar = new QTabBar(this);
    tabBar->addTab("Tree");
    tabBar->addTab("Text");
    tabBar->setShape(QTabBar::RoundedSouth);

    QBoxLayout *layoutHor = new QBoxLayout(QBoxLayout::LeftToRight);
    layoutHor->addWidget(tabBar);
    layoutHor->addStretch();




    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(tree);
    m_stackedWidget->addWidget(text);
    QBoxLayout *layoutVert = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layoutVert->addWidget(m_stackedWidget);
    layoutVert->addLayout(layoutHor);

    connect(tabBar, &QTabBar::currentChanged, this, &DetailPanel::switchTabs );
}


void DetailPanel::switchTabs(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}



