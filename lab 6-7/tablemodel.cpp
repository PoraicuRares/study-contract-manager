#include "tablemodel.h"

int TableModel::rowCount(const QModelIndex& parent) const{
    return (int)discipline.size();
    (void)parent;
}

int TableModel::columnCount(const QModelIndex& parent) const{
    return 4;
    (void)parent;
}

QVariant TableModel::data(const QModelIndex& index, int role) const{
    if (role == Qt::DisplayRole) {
        auto d = discipline[index.row()];
        if (index.column() == 0) {
            return QString::fromStdString(d.getDenumire());
        }
        if (index.column() == 1) {
            return QString::number(d.getOrePeSapt());
        }
        if (index.column() == 2) {
            return QString::fromStdString(d.getTip());
        }
        if (index.column() == 3) {
            return QString::fromStdString(d.getCadruDidactic());
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) return "Denumire";
        if (section == 1) return "Nr.Ore";
        if (section == 2) return "Tip";
        if (section == 3) return "Cadru Didactic";
    }
    return QVariant();
}

void TableModel::setDiscipline(const vector<Disciplina>& disc){
    beginResetModel();
    discipline = disc;
    endResetModel();

}
