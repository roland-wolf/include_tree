#include <QHeaderView>
#include "tableviewheaders.h"

TableViewHeaders::TableViewHeaders(QAbstractItemModel *model)
{
    setModel(model);
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);
    connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this, &TableViewHeaders::onSelectionChanged);

}

void TableViewHeaders::setSelectHeader(ISelectHeader *selectHeader)
{
    m_selectHeader = selectHeader;
}


void TableViewHeaders::onSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
   const int row = current.row();
   QModelIndex modelIndex = model()->index(current.row(), 0);
   QString fileName = model()->data(modelIndex).toString();
   m_selectHeader->selectHeader(fileName);
}
