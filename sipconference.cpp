#include "sipconference.h"

#include <pjsua2.hpp>

#include <QtDebug>

namespace qsua {

SipConference::SipConference(SipCall *call) : call1_(call)
{

}

void SipConference::addCall(SipCall *call)
{
    call2_ = call;
}

void SipConference::start()
{
    if(call1_ == nullptr || call2_ == nullptr) {
        return;
    }

    pj::AudioMedia audioMedia1{};
    pj::AudioMedia audioMedia2{};

    try {
        audioMedia1 = call1_->getAudioMedia(-1);
        audioMedia2 = call2_->getAudioMedia(-1);
    }  catch (pj::Error& error) {
        qWarning() << "Conference error: " << error.reason.c_str() << " " << error.srcFile.c_str() << ":" << error.srcLine << " (" << error.status << ") " << error.title.c_str();
    }

    audioMedia1.startTransmit(audioMedia2);
    audioMedia2.startTransmit(audioMedia1);
}

bool SipConference::removeCall(SipCall *call)
{
    if(call->getId() == (call1_ && call1_->getId())) {
        if(call2_) {
            call1_ = call2_;
            call2_ = nullptr;
            return false;
        } else {
            call1_ = nullptr;
            return true;
        }
    }

    if(call->getId() == (call2_ && call2_->getId())) {
        call2_ = nullptr;
        return false;
    }

    return false;
}

} // namespace qsua
