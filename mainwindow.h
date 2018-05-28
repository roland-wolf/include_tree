#pragma once

#include <QMainWindow>
#include <QAction>

#include "iactions.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *centralWidget, IActions *actions);

private slots:
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionLoadDir_triggered();

private:
    void createMenus();
    void configureActions();

    QAction m_exitAction;
    QAction m_aboutAction;
    QAction m_loadDirAction;

    IActions *m_actions;
};


