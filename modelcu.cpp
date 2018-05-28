#include "modelcu.h"


ModelCu::ModelCu()
{
}

void ModelCu::setLines(const QVector<Line> &lines)
{
    beginResetModel();
    m_lines = lines;
    endResetModel();
}

int ModelCu::rowCount(const QModelIndex &parent) const
{
    return m_lines.size();
}

int ModelCu::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant ModelCu::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int column = index.column();
    if (role == Qt::DisplayRole) {
        if(row < 0 || row >= m_lines.size()){
            return QVariant();
        }
        if(column < 0 || column >= 4){
            return QVariant();
        }
        if(column == 0 ){
            return m_lines.at(row).text;
        } else  if(column == 1 ){
            return m_lines.at(row).direct;
        } else  if(column == 2 ){
            return m_lines.at(row).indirect;
        } else  if(column == 3 ){
            return QString("%L1").arg(m_lines.at(row).size);
        }
    } else if(role == Qt::TextAlignmentRole){
        if(column == 0 ){
            return QVariant(Qt::AlignLeft);
        }else {
            return QVariant(Qt::AlignRight);
        }
        return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags ModelCu::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled ;
}

QVariant ModelCu::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        switch (section){
        case 0:
            return QString("Compilation Unit");
            break;
        case 1:
            return QString("direct");
            break;
        case 2:
            return QString("indirect");
            break;
        case 3:
            return QString("total");
            break;
        default:
            return QVariant();
        }
    } else if ((orientation == Qt::Horizontal) && (role == Qt::TextAlignmentRole)) {
        if(section == 0){
              return Qt::AlignLeft;
        }
            return Qt::AlignRight;
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}



Line::Line()
    : direct(0)
    , indirect(0)
    , size(0)
{

}
