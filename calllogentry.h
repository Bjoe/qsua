#ifndef QSUA_CALLLOGENTRY_H
#define QSUA_CALLLOGENTRY_H

#include "sipcall.h"

#include <QObject>
#include <QVector>
#include <QString>

namespace qsua {

class CallLogEntry : public QObject
{
    Q_OBJECT
public:
    CallLogEntry(int row, SipCall* call, QObject* parent = nullptr);

    SipCall* call() const; // TODO Refactor to use callId
    QString remoteUri() const;
    QString state() const;

public slots:
    void onCallStateChanged(QString stateTxt, int state);

signals:
    void entryChanged(int row, const QVector<int> &roles = QVector<int>());

private:
    int row_;
    SipCall* call_;
    QString remoteUri_{};
    QString state_{};
};

} // namespace qsua

#endif // QSUA_CALLLOGENTRY_H
