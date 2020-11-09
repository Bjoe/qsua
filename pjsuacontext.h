#ifndef QSUA_PJSUACONTEXT_H
#define QSUA_PJSUACONTEXT_H

#include "calllistmodel.h"
#include "pjsuacore.h"

#include <QString>
#include <QObject>

namespace qsua {

class SipAccount;

class PjSuaContext : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CallListModel* model READ model NOTIFY modelChanged)

public:
    PjSuaContext(QObject *parent = nullptr);

    CallListModel *model() const;

public slots:
    void onCreateAccount();
    void onMakeCall(const QString &uri);
    void onIncomingCall(SipCall* call);

signals:
    void modelChanged();
    void regStateChanged(bool regIsActive, QString statusTxt);

private:
    PjSuaCore core_{};
    SipAccount *account_{};
    CallListModel *model_{new CallListModel(this)};
};

} // namespace qsua

#endif // QSUA_PJSUACONTEXT_H
