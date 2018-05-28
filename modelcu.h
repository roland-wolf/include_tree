#ifndef MODELCU_H
#define MODELCU_H

#include <QAbstractTableModel>
#include <QVector>

struct Line
{
    Line();
    QString text;
    int direct;
    int indirect;
    int size;
};


class ModelCu : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelCu();
    void setLines(const QVector<Line> &lines);

private:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    QVector<Line> m_lines;
};

#endif // MODELCU_H
