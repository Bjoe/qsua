#ifndef QSUA_SIPLOGWRITER_H
#define QSUA_SIPLOGWRITER_H

#include <pjsua2.hpp>

namespace qsua {

class SipLogWriter : public pj::LogWriter
{
public:
    SipLogWriter();

    // LogWriter interface
public:
    void write(const pj::LogEntry &entry) override;
};

} // namespace qsua

#endif // QSUA_SIPLOGWRITER_H
