#ifndef QSUA_PJSUACONTEXT_H
#define QSUA_PJSUACONTEXT_H

#include "calllistmodel.h"
#include "sipconference.h"
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
    void onMakeCall(const QString &uri);
    void onAddCall(qsua::SipCall *call);
    void onConference();
    void onCreateAccount();

signals:
    void start();
    void makeCall(const QString &uri);
    void createAccount();
    void modelChanged();
    void regStateChanged(bool regIsActive, QString statusTxt);

private:
    PjSuaCore core_{};
    CallListModel *model_{new CallListModel(this)};
    SipConference conference_{};
};

} // namespace qsua

#endif // QSUA_PJSUACONTEXT_H
