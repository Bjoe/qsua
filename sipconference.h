#ifndef QSUA_SIPCONFERENCE_H
#define QSUA_SIPCONFERENCE_H

#include "sipcall.h"

#include <vector>

namespace qsua {

class SipConference
{
public:
    SipConference();

    void addCall(int callId);
    void start();

    void removeCall(int callId);

public:
    std::vector<int> calls_{};
};

} // namespace qsua

#endif // QSUA_SIPCONFERENCE_H
