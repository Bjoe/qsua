#ifndef QSUA_SIPCONFERENCE_H
#define QSUA_SIPCONFERENCE_H

#include "sipcall.h"

#include <QObject>
#include <vector>

namespace qsua {

class SipConference : public QObject
{
    Q_OBJECT
public:
    SipConference(QObject* parent = nullptr);

    void addCall(int callId);
    void start();

public slots:
    void removeCall(int callId);

public:
    std::vector<int> calls_{};
};

} // namespace qsua

#endif // QSUA_SIPCONFERENCE_H
