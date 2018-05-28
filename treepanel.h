#pragma once

#include <QWidget>
#include <QAction>

class QTreeView;
class QLineEdit;

class   TreePanel : public QWidget
{
    Q_OBJECT
public:
    explicit TreePanel(QTreeView *tree);

private slots:
    void collapse();
    void expand();
    void parents();
    void next();
    void previous();

private:
    QAction m_actionExpand;
    QAction m_actionCollapse;
    QAction m_actionParents;

    QAction m_actionNext;
    QAction m_actionPrevious;

    QTreeView *m_treeView;
    QLineEdit *m_lineEdit;
};

