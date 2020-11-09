#ifndef QSUA_SIPCALL_H
#define QSUA_SIPCALL_H

#include <pjsua2.hpp>
#include <QString>
#include <QObject>

namespace qsua {

class SipAccount;

class SipCall : public QObject, public pj::Call
{
    Q_OBJECT

public:
    SipCall &operator=(const SipCall&) = default;


    SipCall(SipAccount* account, int callId = PJSUA_INVALID_ID);

    std::string remoteUri() const;
    std::string stateText() const;

    Q_INVOKABLE void accept();
    Q_INVOKABLE void decline();
    Q_INVOKABLE void hangup();

signals:
    void stateChanged(QString stateTxt);//, pjsip_inv_state state);

    // Call interface
protected:
    void onCallState(pj::OnCallStateParam &prm) override;
    void onCallMediaState(pj::OnCallMediaStateParam &prm) override;
};

} // namespace qsua

#endif // QSUA_SIPCALL_H
