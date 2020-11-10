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

void CallLogEntry::onCallStateChanged(QString stateTxt)//, pjsip_inv_state state)
{
    // TODO if pjsip_inv_state state is PJSIP_INV_STATE_DISCONNECTED then delete call_;
    // TODO also delete call object in SipConference

    state_ = stateTxt;
    emit entryChanged(row_, { Qt::UserRole+2 });
}

} // namespace qsua
