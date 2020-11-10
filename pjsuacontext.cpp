#include "pjsuacontext.h"

#include "calllistmodel.h"
#include "sipcall.h"

#include <string>
#include <QSettings>

#include <QDebug>

namespace qsua {

PjSuaContext::PjSuaContext(QObject *parent) : QObject(parent)
{
    core_.onPjsuaStart();
    onCreateAccount();
    emit modelChanged();
}

void PjSuaContext::onCreateAccount()
{
    QSettings settings;
    std::string pjsuaAccConfigId = settings.value("pjsuaAccConfigId").toString().toStdString();
    std::string pjsuaAccConfigRegUri = settings.value("pjsuaAccConfigRegUri").toString().toStdString();
    std::string pjsipCredInfoScheme = settings.value("pjsipCredInfoScheme").toString().toStdString();
    std::string pjsipCredInfoRealm = settings.value("pjsipCredInfoRealm").toString().toStdString();
    std::string pjsipCredInfoUsername = settings.value("pjsipCredInfoUsername").toString().toStdString();
    std::string pjsipCredInfoData = settings.value("pjsipCredInfoData").toString().toStdString();

    if(pjsuaAccConfigId.empty() &&
               pjsuaAccConfigRegUri.empty() &&
               pjsipCredInfoScheme.empty() &&
               pjsipCredInfoRealm.empty() &&
               pjsipCredInfoUsername.empty() &&
               pjsipCredInfoData.empty())
    {
        qWarning() << "Settings are empty!";
        return;
    }

    if(account_) {
        delete account_;
    }

    pj::AccountConfig accountConfig{};
    accountConfig.idUri = pjsuaAccConfigId;
    accountConfig.regConfig.registrarUri = pjsuaAccConfigRegUri;

    pj::AuthCredInfo authCredentials(pjsipCredInfoScheme, pjsipCredInfoRealm, pjsipCredInfoUsername, 0, pjsipCredInfoData);

    accountConfig.sipConfig.authCreds.push_back(authCredentials);

    account_ = new SipAccount();
    connect(account_, &SipAccount::regStateChanged, this, &PjSuaContext::regStateChanged);
    connect(account_, &SipAccount::incomingCall, this, &PjSuaContext::onIncomingCall);

    account_->create(accountConfig);
    qDebug() << "Account created!";
}

void PjSuaContext::onMakeCall(const QString& uri)
{
    // Make outgoing call
    SipCall *call = new SipCall(account_);

    pj::CallOpParam prm(true);
    prm.opt.audioCount = 1;
    prm.opt.videoCount = 0;
    try {
        call->makeCall(uri.toStdString(), prm);
    }  catch (pj::Error& e) {
        qWarning() << "Make call failed: " << e.reason.c_str() << " src File: " << e.srcFile.c_str() << " : " << e.srcLine << " (" << e.status << ") " << e.title.c_str();
    }

    model_->addCall(call);
    qDebug() << "Make call" << uri << "started";

    conference_.addCall(call->getId());
    connect(call, &SipCall::disconnected, &conference_, &SipConference::removeCall);
}

CallListModel* PjSuaContext::model() const
{
    return model_;
}

void PjSuaContext::onIncomingCall(SipCall *call)
{
    model_->addCall(call);

    conference_.addCall(call->getId());
    connect(call, &SipCall::disconnected, &conference_, &SipConference::removeCall);
}

void PjSuaContext::onConference()
{
    conference_.start();
}


} // namespace qsua
