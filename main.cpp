#include <QApplication>
#include <QWidget>
#include "maincontainer.h"
#include "treemodel.h"
#include "actions.h"

int main(int argc, char *argv[])
{
     Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);
    //TreeModel treeModel;

    //Actions actions(&treeModel);
    //MainWindow mainWindow(&treeModel, &actions);
    //actions.setGuiInterface(&mainWindow);

    MainContainer mainContainer;

    QWidget &mainWindow = mainContainer.mainWindow();

    //actions.loadSingleFile("/home/roland/Documents/kdevelop/include_tree/build/mainwindow.ii");


    //actions.loadAllFiles("/home/roland/Documents/kdevelop/preprocessed_files");

    //mainWindow.resizeColumns();
    mainWindow.show();

    app.exec();
}
