#ifndef QSUA_SIPCONFERENCE_H
#define QSUA_SIPCONFERENCE_H

#include "sipcall.h"

namespace qsua {

class SipConference
{
public:
    SipConference(SipCall* call);

    void addCall(SipCall* call);
    void start();

    bool removeCall(SipCall* call);

public:
    SipCall* call1_;
    SipCall* call2_;
};

} // namespace qsua

#endif // QSUA_SIPCONFERENCE_H
