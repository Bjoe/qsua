#include "pjsuacontext.h"

#include "calllistmodel.h"
#include "sipcall.h"

#include <string>

#include <QDebug>

namespace qsua {

PjSuaContext::PjSuaContext(QObject *parent) : QObject(parent)
{
    connect(this, &PjSuaContext::start, &core_, &PjSuaCore::onPjsuaStart);
    connect(&core_, &PjSuaCore::incomingCall, this, &PjSuaContext::onAddCall);
    connect(&core_, &PjSuaCore::newCall, this, &PjSuaContext::onAddCall);
    connect(&core_, &PjSuaCore::regStateChanged, this, &PjSuaContext::regStateChanged);
    connect(this, &PjSuaContext::makeCall, &core_, &PjSuaCore::onMakeCall);
    connect(this, &PjSuaContext::createAccount, &core_, &PjSuaCore::onCreateAccount);
}

void PjSuaContext::onMakeCall(const QString& uri)
{
    emit makeCall(uri);
}

CallListModel* PjSuaContext::model() const
{
    return model_;
}

void PjSuaContext::onAddCall(SipCall *call)
{
    model_->addCall(call);

    conference_.addCall(call->getId());
    connect(call, &SipCall::disconnected, &conference_, &SipConference::removeCall);
}

void PjSuaContext::onConference()
{
    conference_.start();
}

void PjSuaContext::onCreateAccount()
{
    emit createAccount();
}


} // namespace qsua
