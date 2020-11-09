#ifndef QSUA_SIPACCOUNT_H
#define QSUA_SIPACCOUNT_H

#include <QObject>
#include <pjsua2.hpp>

namespace qsua {

class SipCall;

class SipAccount : public QObject, public pj::Account
{
    Q_OBJECT

public:
    explicit SipAccount(QObject* parent = nullptr);

    // Account interface
public:
    void onRegState(pj::OnRegStateParam &prm) override;
    void onIncomingCall(pj::OnIncomingCallParam &prm) override;

signals:
    void incomingCall(SipCall* call);
    void regStateChanged(bool regIsActive, QString statusTxt);
};

} // namespace qsua

#endif // QSUA_SIPACCOUNT_H
