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
    SipCall(SipAccount* account, int callId = PJSUA_INVALID_ID);

    std::string remoteUri() const;
    std::string stateText() const;

    Q_INVOKABLE void accept(); // TODO use callid and do not use ui thread
    Q_INVOKABLE void decline(); // TODO use callid and do not use ui thread
    Q_INVOKABLE void hangup(); // TODO use callid and do not use ui thread

signals:
    void stateChanged(QString stateTxt, int state);
    void disconnected(int callId);

    // Call interface
protected:
    void onCallState(pj::OnCallStateParam &prm) override;
    void onCallMediaState(pj::OnCallMediaStateParam &prm) override;
};

} // namespace qsua

#endif // QSUA_SIPCALL_H
