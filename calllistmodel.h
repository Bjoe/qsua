#ifndef QSUA_CALLLISTMODEL_H
#define QSUA_CALLLISTMODEL_H

#include "calllogentry.h"

#include <QList>
#include <QAbstractListModel>

namespace qsua {

class CallListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CallListModel(QObject *parent = nullptr);

    void addCall(SipCall *call);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void onDataChapnged(int row, const QVector<int> &roles = QVector<int>());

private:
    QList<CallLogEntry*> itemList_;

};

} // namespace qsua

#endif // QSUA_CALLLISTMODEL_H
