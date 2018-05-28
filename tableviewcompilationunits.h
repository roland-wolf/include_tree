#ifndef TABLEVIEWCOMPILATIONUNITS_H
#define TABLEVIEWCOMPILATIONUNITS_H

#include <QTableView>
#include "iselectcu.h"

class TableViewCompilationUnits : public QTableView
{
    Q_OBJECT
public:
    TableViewCompilationUnits(QAbstractItemModel *model);
    void setSelectCu(ISelectCu *selectCu);

private slots:
     void onSelectionChanged(const QModelIndex &current, const QModelIndex &previous);

private:
      ISelectCu *m_selectCu;
};

#endif // TABLEVIEWCOMPILATIONUNITS_H
