#include "calllogentry.h"

namespace qsua {

CallLogEntry::CallLogEntry(int row, SipCall *call, QObject* parent) : QObject(parent), row_(row), call_(call)
{
    connect(call, &SipCall::stateChanged, this, &CallLogEntry::onCallStateChanged);
    remoteUri_ = QString(call->remoteUri().c_str());
    state_ = QString(call->stateText().c_str());
}

SipCall *CallLogEntry::call() const
{
    return call_;
}

QString CallLogEntry::remoteUri() const
{
    return remoteUri_;
}

QString CallLogEntry::state() const
{
    return state_;
}

void CallLogEntry::onCallStateChanged(QString stateTxt, int state)
{
    // TODO also delete call object in SipConference

    state_ = stateTxt;
    emit entryChanged(row_, { Qt::UserRole+2 });

    if(state == PJSIP_INV_STATE_DISCONNECTED) {
        delete call_;
    }
}

} // namespace qsua
