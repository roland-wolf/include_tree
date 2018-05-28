#pragma once

#include <QSplitter>

class CentralWidget : public QSplitter
{
    Q_OBJECT
public:
    CentralWidget(QWidget *left, QWidget* right);
};


