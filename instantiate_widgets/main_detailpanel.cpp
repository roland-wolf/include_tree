#include <QApplication>
#include "detailpanel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget widgetLeft;
    widgetLeft.setForegroundRole(QPalette::Text);
    widgetLeft.setStyleSheet("background-color:black;");

    QWidget widgetRight;
    widgetRight.setStyleSheet("background-color:blue;");
    DetailPanel centralWidget(&widgetLeft, &widgetRight);

    centralWidget.setGeometry(100, 100, 200, 200);
    centralWidget.show();

    app.exec();
}
