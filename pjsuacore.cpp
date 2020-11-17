#include "pjsuacore.h"

#include "sipcall.h"
#include "siplogwriter.h"

#include <QDebug>
#include <QSettings>

namespace qsua {

PjSuaCore::PjSuaCore(QObject *parent) : QObject(parent)
{
}

void PjSuaCore::onHangupAllCalls()
{
    pjCore_.hangupAllCalls();
}

void PjSuaCore::onPjsuaStart()
{
    if(pjCore_.libGetState() != pjsua_state::PJSUA_STATE_NULL)
    {
        qWarning() << "PjSua lib are initialized! Restart PjSua lib ...";
        pjCore_.libDestroy();
    }

    pjCore_.libCreate();

    pj::EpConfig epCfg{};
    epCfg.logConfig.level = 5;
    epCfg.logConfig.writer = new SipLogWriter();

    epCfg.medConfig.sndClockRate = 0;
    epCfg.medConfig.sndPlayLatency = 80;
    epCfg.medConfig.sndRecLatency = 80;
    epCfg.medConfig.channelCount = 1;
    epCfg.medConfig.threadCnt = 2;
    epCfg.medConfig.quality = 9;
    epCfg.medConfig.hasIoqueue = true;
    epCfg.medConfig.ptime = 80;
    epCfg.medConfig.noVad = true;

    epCfg.medConfig.jbInit = 180;
    epCfg.medConfig.jbMax = 300;
    epCfg.medConfig.jbMaxPre = 180;
    epCfg.medConfig.jbMinPre = 180;

    pjCore_.libInit(epCfg);


    pj::TransportConfig transportCfg{};
    transportCfg.port = 5060;
    try {
        pjCore_.transportCreate(PJSIP_TRANSPORT_UDP, transportCfg);
    }  catch (const pj::Error &err) {
        qWarning() << "Create transport failed" << err.info().c_str();
        return;
    }

    pjCore_.libStart();
    qDebug() << "PjSua lib started!";

    int dev_count = pjmedia_aud_dev_count();
    qDebug() << "Got" << dev_count << "audio devices";
    for (pjmedia_aud_dev_index dev_idx=0; dev_idx < dev_count; ++dev_idx) {
        pjmedia_aud_dev_info info;
        pjmedia_aud_dev_get_info(dev_idx, &info);
        qDebug() << dev_idx << ". " << info.name << "(in=" << info.input_count << "out=" << info.output_count << ")";
    }

    /*pjmedia_aud_dev_info info;
    pj_status_t status = pjmedia_aud_dev_get_info(PJMEDIA_AUD_DEFAULT_CAPTURE_DEV, &info);
    if (status == PJ_SUCCESS) {
        // Enumerate capability bits
        qDebug() << "Device capabilities: ";
        for (unsigned i=0; i<32; ++i) {
            if (info.caps & (1 << i))
                qDebug() << pjmedia_aud_dev_cap_name(info.caps, NULL));
        }
    }*/

    /*pj::AudDevManager& amanager = pjCore_.audDevManager();
    amanager.setCaptureDev(0);
    amanager.setPlaybackDev(0);*/
}

void PjSuaCore::onCreateAccount()
{
    if(createAccountThread_) {
       createAccountThread_->join();
       delete createAccountThread_;
       free(pjCreateCreateAccountThreadDesc_);
    }
    createAccountThread_ = new std::thread(&PjSuaCore::createAccountWorker, this);
}

void PjSuaCore::onMakeCall(const QString &uri)
{
    if(callThread_) {
        callThread_->join();
        delete callThread_;
        free(pjCallThreadDesc_);
    }
    callThread_ = new std::thread(&PjSuaCore::makeCallWorker, this, uri);
}

void PjSuaCore::makeCallWorker(const QString &uri)
{
    // Make outgoing call
    SipCall *call = new SipCall(account_);

    pj::CallOpParam prm(true);
    prm.opt.audioCount = 1;
    prm.opt.videoCount = 0;
    try {
        qDebug() << "Make call" << uri;
        pjCallThreadDesc_ = (pj_thread_desc*)malloc(sizeof(pj_thread_desc));
        if (!pjCallThreadDesc_) {
            qWarning() << "Settings are empty!";
            return;
        }
        pj_bzero(pjCallThreadDesc_, sizeof(pj_thread_desc));
        pj_status_t st = pj_thread_register("makeCallWorkerQThread",
                                            *pjCallThreadDesc_,
                                            &pjCallThread_);
        if(st != PJ_SUCCESS) {
            qWarning() << "Cannot register thread for PjSip statck";
            return;
        }

        call->makeCall(uri.toStdString(), prm);
    }  catch (pj::Error& e) {
        qWarning() << "Make call failed: " << e.reason.c_str() << " src File: " << e.srcFile.c_str() << " : " << e.srcLine << " (" << e.status << ") " << e.title.c_str();
    }
    emit newCall(call);
}

void PjSuaCore::createAccountWorker()
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

    pjCreateCreateAccountThreadDesc_ = (pj_thread_desc*)malloc(sizeof(pj_thread_desc));
    if (!pjCreateCreateAccountThreadDesc_) {
        qWarning() << "Settings are empty!";
        return;
    }
    pj_bzero(pjCreateCreateAccountThreadDesc_, sizeof(pj_thread_desc));
    pj_status_t st = pj_thread_register("createAccountWorkerQThread",
                                        *pjCreateCreateAccountThreadDesc_,
                                        &pjCreateAccountThread_);
    if(st != PJ_SUCCESS) {
        qWarning() << "Cannot register thread for PjSip statck";
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
    connect(account_, &SipAccount::regStateChanged, this, &PjSuaCore::regStateChanged);
    connect(account_, &SipAccount::incomingCall, this, &PjSuaCore::incomingCall);

    account_->create(accountConfig);
    qDebug() << "Account created!";
}

void PjSuaCore::onPjsuaDestroy()
{
    pjCore_.libDestroy();
}

} // namespace qsua
