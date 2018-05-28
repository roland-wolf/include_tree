#include <QHeaderView>
#include <QItemSelectionModel>

#include "tableviewcompilationunits.h"

TableViewCompilationUnits::TableViewCompilationUnits(QAbstractItemModel *model)
{
   horizontalHeader()->setVisible(true);
   verticalHeader()->setVisible(true);
   setSelectionBehavior(QAbstractItemView::SelectRows);
   setSelectionMode(QAbstractItemView::SingleSelection);
   //verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   setModel(model);

   connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this, &TableViewCompilationUnits::onSelectionChanged);
}

void TableViewCompilationUnits::setSelectCu(ISelectCu *selectCu)
{
    m_selectCu = selectCu;
}


void TableViewCompilationUnits::onSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
   const int row = current.row();
   QModelIndex modelIndex = model()->index(current.row(), 0);
   QString fileName = model()->data(modelIndex).toString();
   m_selectCu->selectCu(fileName);
}
