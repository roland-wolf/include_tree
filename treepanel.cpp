#include <QToolBar>
#include <QLineEdit>
#include <QSpacerItem>
#include <QBoxLayout>
#include <QTreeView>
#include <QIcon>

#include "treepanel.h"

TreePanel::TreePanel(QTreeView *tree)
    : m_treeView(tree)
{
    m_actionCollapse.setText("Collapse");
    m_actionExpand.setText("Expand");
    m_actionParents.setText("Parents");
    m_actionNext.setIcon(QIcon(":lc_nextpage.png"));
    m_actionPrevious.setIcon(QIcon(":/lc_previouspage.png"));
    connect(&m_actionCollapse, &QAction::triggered, this, &TreePanel::collapse);
    connect(&m_actionExpand, &QAction::triggered, this, &TreePanel::expand);
    connect(&m_actionParents, &QAction::triggered, this, &TreePanel::parents);
    connect(&m_actionNext, &QAction::triggered, this, &TreePanel::next);
    connect(&m_actionPrevious, &QAction::triggered, this, &TreePanel::previous);

    QBoxLayout *boxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    boxLayout->setMargin(0);

    m_lineEdit = new QLineEdit;
    QToolBar *toolBar = new QToolBar;
    toolBar->addAction(&m_actionExpand);
    toolBar->addAction(&m_actionCollapse);
    toolBar->addAction(&m_actionParents);

    QToolBar *toolBarRight = new QToolBar;
    toolBarRight->addAction(&m_actionPrevious);
    toolBarRight->addAction(&m_actionNext);

    QBoxLayout *boxLayoutHor = new QBoxLayout(QBoxLayout::LeftToRight);
    boxLayoutHor->addWidget(toolBar);
    QSpacerItem *spacerItem = new QSpacerItem(0,0,QSizePolicy::Expanding);
    boxLayoutHor->addSpacerItem(spacerItem);
    boxLayoutHor->addWidget(m_lineEdit);
    boxLayoutHor->addWidget(toolBarRight);

    boxLayout->addLayout(boxLayoutHor);
    boxLayout->addWidget(tree);
}


void TreePanel::collapse()
{
    m_treeView->collapseAll();
}


void TreePanel::expand()
{
    m_treeView->expandAll();
}

void TreePanel::parents()
{
    QModelIndex index = m_treeView->currentIndex();
    QVector<QModelIndex> indexes;
    while(index != QModelIndex()){
        indexes.push_back(index);
        index = index.parent();
    }
    m_treeView->collapseAll();
    for(const auto &index : indexes){
        m_treeView->expand(index);
    }
}

void TreePanel::next()
{
    //finds all matches below current Index. Needs a rewrite to find next.
    QString text = m_lineEdit->text();
    QAbstractItemModel *model = m_treeView->model();

    QModelIndex current = m_treeView->currentIndex();
    QModelIndexList indexes = model->match(current, Qt::DisplayRole, text, -1,  Qt::MatchRecursive | Qt::MatchContains);

    for(auto const &index : indexes){
        m_treeView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}

void TreePanel::previous()
{
}
