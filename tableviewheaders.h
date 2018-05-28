#ifndef TABLEVIEWHEADERS_H
#define TABLEVIEWHEADERS_H

#include <QTableView>

#include "iselectcu.h"

class TableViewHeaders : public QTableView
{
    Q_OBJECT
public:
    TableViewHeaders(QAbstractItemModel *model);
    void setSelectHeader(ISelectHeader *selectHeader);

private slots:
     void onSelectionChanged(const QModelIndex &current, const QModelIndex &previous);

private:
      ISelectHeader *m_selectHeader;

};

#endif // TABLEVIEWHEADERS_H
