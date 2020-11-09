#include "sipaccount.h"

#include "sipcall.h"

#include <QDebug>

namespace qsua {

SipAccount::SipAccount(QObject *parent) : QObject(parent)
{

}

void SipAccount::onRegState(pj::OnRegStateParam &prm)
{
    pj::AccountInfo ai = getInfo();
    qDebug() << (ai.regIsActive? "*** Register:" : "*** Unregister:") << " code=" << prm.code;

    QString t = QString::fromStdString(prm.reason);
    emit regStateChanged(ai.regIsActive, t);
}

void SipAccount::onIncomingCall(pj::OnIncomingCallParam &iprm)
{
    SipCall* call = new SipCall(this, iprm.callId);
    pj::CallInfo ci = call->getInfo();

    qDebug() << "*** Incoming Call: " <<  ci.remoteUri.c_str() << " [" << ci.stateText.c_str() << "]";

    emit incomingCall(call);
}

} // namespace qsua
