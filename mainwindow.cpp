#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *centralWidget, IActions *actions)
    : m_actions(actions)
{
    setCentralWidget(centralWidget);
    configureActions();
    createMenus();

    //m_actions->loadAllFiles("/home/roland/Documents/kdevelop/include_tree/build");
}


void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(&m_loadDirAction);
    fileMenu->addAction(&m_exitAction);
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(&m_aboutAction);
}


void MainWindow::configureActions()
{
    m_exitAction.setText("Exit");
    m_aboutAction.setText("About");
    m_loadDirAction.setText("Load Directory ...");

    connect(&m_aboutAction, &QAction::triggered, this, &MainWindow::on_actionAbout_triggered);
    connect(&m_exitAction, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
    connect(&m_loadDirAction, &QAction::triggered, this, &MainWindow::on_actionLoadDir_triggered);
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "IncludeTree", "Analyse cost of C/C++ include statements");
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionLoadDir_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open build directory containing preprocessed files");
    if(dir.isEmpty()){
        return;
    }
    m_actions->loadAllFiles(dir);
}

