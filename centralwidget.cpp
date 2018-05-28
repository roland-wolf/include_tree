#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *left, QWidget *right)
{
    addWidget(left);
    addWidget(right);
}
