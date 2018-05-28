#include "maincontainer.h"
#include "mainwindow.h"
#include "centralwidget.h"
#include "overviewpanel.h"
#include "detailpanel.h"
#include "tableviewcompilationunits.h"
#include "tableviewheaders.h"
#include "modelcu.h"
#include "actions.h"
#include "treemodel.h"
#include "parsepreprocessed.h"
#include "treepanel.h"
#include "plaintextedit.h"


#include <QStandardItemModel>
#include <QTreeView>


MainContainer::MainContainer()
{
    ModelCu *itemModelCu = new ModelCu;
    ModelCu *itemModelHu = new ModelCu;

    m_tableViewCompilationUnits = new TableViewCompilationUnits(itemModelCu);
    m_tableViewHeaders = new TableViewHeaders(itemModelHu);
    m_overviewPanel = new OverviewPanel(m_tableViewCompilationUnits, m_tableViewHeaders);

    TreeModel *treeModel = new TreeModel;
    QTreeView *treeView = new QTreeView;
    m_treePanel = new TreePanel(treeView);
    treeModel->setParent(m_treePanel);
    treeView->setModel(treeModel);
    m_plainTextEdit = new PlainTextEdit;
    m_plainTextEdit->setReadOnly(true);
    m_detailPanel = new DetailPanel(m_treePanel, m_plainTextEdit);
    m_centralWidget = new CentralWidget(m_overviewPanel, m_detailPanel);

    m_actions = std::make_unique<Actions>(treeModel, itemModelCu, itemModelHu, m_plainTextEdit);
    m_tableViewCompilationUnits->setSelectCu(m_actions.get());
    m_tableViewHeaders->setSelectHeader(m_actions.get());
    m_mainWindow = new MainWindow(m_centralWidget, m_actions.get());
}


MainContainer::~MainContainer()
{
    delete m_mainWindow;
}

QWidget &MainContainer::mainWindow()
{
    return *m_mainWindow;
}
