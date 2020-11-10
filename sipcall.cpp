#include "sipcall.h"

#include "sipaccount.h"

#include <QDebug>

namespace qsua {


SipCall::SipCall(SipAccount *account, int callId) : QObject(account), pj::Call(*account, callId)
{

}

std::string SipCall::remoteUri() const
{
    pj::CallInfo ci = pj::Call::getInfo();
    std::string o = ci.remoteUri;
    return o;
}

std::string SipCall::stateText() const
{
    pj::CallInfo ci = pj::Call::getInfo();
    std::string state = ci.stateText;
    return state;
}

void SipCall::accept()
{
    pj::CallOpParam prm;
    prm.statusCode = static_cast<pjsip_status_code>(200);
    pj::Call::answer(prm);
}

void SipCall::decline()
{
    pj::CallOpParam prm;
    prm.statusCode = static_cast<pjsip_status_code>(603);
    pj::Call::answer(prm);
}

void SipCall::hangup()
{
    pj::CallOpParam prm;
    pj::Call::hangup(prm);
}

void SipCall::onCallState([[maybe_unused]] pj::OnCallStateParam &prm)
{
    pj::CallInfo ci = pj::Call::getInfo();
    QString stateTxt{ci.stateText.c_str()};
    qDebug() << "*** Call: " <<  ci.remoteUri.c_str() << " [" << stateTxt << "]";

    emit stateChanged(stateTxt, ci.state);
}

void SipCall::onCallMediaState([[maybe_unused]] pj::OnCallMediaStateParam &prm)
{
    pj::AudioMedia audioMedia{};
    try {
        // Get the first audio media
        audioMedia = pj::Call::getAudioMedia(-1);
    }  catch (...) {
        qWarning() << "onCallMediaState() Call::getAudioMedia failed!";
        return;
    }


    pj::AudioMedia& capDevMedia = pj::Endpoint::instance().audDevManager().getCaptureDevMedia();

    // This will connect the sound device/mic to the call audio media
    capDevMedia.startTransmit(audioMedia);


    pj::AudioMedia& playDevMedia = pj::Endpoint::instance().audDevManager().getPlaybackDevMedia();

    // And this will connect the call audio media to the sound device/speaker
    audioMedia.startTransmit(playDevMedia);
}

} // namespace qsua
