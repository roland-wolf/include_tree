#pragma once

#include <memory>

class MainWindow;
class DetailPanel;
class OverviewPanel;
class CentralWidget;
class TableViewHeaders;
class TableViewCompilationUnits;
class Actions;
class TreeModel;
class TreePanel;
class QTreeView;
class PlainTextEdit;
class QWidget;


class MainContainer
{
public:
    MainContainer();
    ~MainContainer();

    QWidget &mainWindow();

private:
    TableViewCompilationUnits *m_tableViewCompilationUnits;
    TableViewHeaders *m_tableViewHeaders;
    OverviewPanel *m_overviewPanel;
    TreePanel *m_treePanel;
    PlainTextEdit *m_plainTextEdit;
    DetailPanel *m_detailPanel;
    CentralWidget *m_centralWidget;
    TreeModel *m_treeModel;
    std::unique_ptr<Actions> m_actions;
    QWidget *m_mainWindow;
};


