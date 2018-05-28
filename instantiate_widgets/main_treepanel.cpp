#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include "treepanel.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app(argc, argv);
    QStandardItemModel model(4,3);
    model.setData(model.index(0,0), QString("hello"));
    model.setData(model.index(1,1), QString("crazy"));
    model.setData(model.index(2,0), QString("world"));
    QTreeView *tree = new QTreeView;
    tree->setModel(&model);
    TreePanel treePanel(tree);
    treePanel.setGeometry(100, 100, 200, 200);
    treePanel.show();
    app.exec();
}
