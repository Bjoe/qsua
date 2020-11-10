#include "sipconference.h"

#include <pjsua2.hpp>

#include <algorithm>
#include <QtDebug>

namespace qsua {

SipConference::SipConference(QObject *parent) : QObject(parent)
{

}

void SipConference::addCall(int callId)
{
    calls_.push_back(callId);
}

void SipConference::start()
{
    if(calls_.size() < 2) {
        qDebug() << "Conference not possible. Less then two calls.";
        return;
    }

    pj::Call* call1 = pj::Call::lookup(calls_.at(0));
    pj::Call* call2 = pj::Call::lookup(calls_.at(1));

    if(     !call1->isActive() ||
            !call1->hasMedia() ||
            !call2->isActive() ||
            !call2->hasMedia()) {
        qDebug() << "Conference not possible, no two active calls.";
        return;
    }

    pj::AudioMedia audioMedia1{};
    pj::AudioMedia audioMedia2{};

    try {
        audioMedia1 = call1->getAudioMedia(-1);
        audioMedia2 = call2->getAudioMedia(-1);
    }  catch (pj::Error& error) {
        qWarning() << "Conference error: " << error.reason.c_str() << " " << error.srcFile.c_str() << ":" << error.srcLine << " (" << error.status << ") " << error.title.c_str();
    }

    audioMedia1.startTransmit(audioMedia2);
    audioMedia2.startTransmit(audioMedia1);
}


void SipConference::removeCall(int callId)
{
    auto result = std::find(std::begin(calls_), std::end(calls_), callId);
    if(result != std::end(calls_)) {
        calls_.erase(result);
    }
}

} // namespace qsua
