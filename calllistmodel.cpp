#include "calllistmodel.h"

namespace qsua {

CallListModel::CallListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void CallListModel::addCall(SipCall *call)
{
    int row = rowCount(QModelIndex());
    CallLogEntry* entry = new CallLogEntry(row, call, this);
    connect(entry, &CallLogEntry::entryChanged, this, &CallListModel::onDataChapnged);

    beginInsertRows(QModelIndex(), row, row);
    itemList_.append(entry);
    endInsertRows();
}

int CallListModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
    return itemList_.count();
}

QHash<int, QByteArray> qsua::CallListModel::roleNames() const
{
    auto r = QAbstractListModel::roleNames();
    r.insert(Qt::UserRole+1, "callObj");
    r.insert(Qt::UserRole+2, "state");
    return r;
}

void qsua::CallListModel::onDataChapnged(int row, const QVector<int> &roles)
{
    QModelIndex i = index(row);
    emit dataChanged(i, i, roles);
}

QVariant CallListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= itemList_.count()) {
        return QVariant();
    }

    CallLogEntry* c = itemList_[index.row()];

    QVariant result{};
    switch(role)
    {
    case Qt::DisplayRole:
        result = QVariant(c->remoteUri());
        break;
    case Qt::UserRole+1:
        result = QVariant::fromValue(c->call());
        break;
    case Qt::UserRole+2:
        result = QVariant(c->state());
        break;
    }
    return result;
}

} // namespace qsua


