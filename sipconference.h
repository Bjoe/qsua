#ifndef QSUA_SIPCONFERENCE_H
#define QSUA_SIPCONFERENCE_H

#include "sipcall.h"

#include <vector>

namespace qsua {

class SipConference
{
public:
    SipConference();

    void addCall(SipCall* call);
    void start();

    void removeCall(SipCall* call);

public:
    std::vector<SipCall*> calls_{};
};

} // namespace qsua

#endif // QSUA_SIPCONFERENCE_H
