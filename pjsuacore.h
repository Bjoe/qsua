#ifndef QSUA_PJSUACORE_H
#define QSUA_PJSUACORE_H

#include "sipaccount.h"

#include <pjsua2.hpp>
#include <QObject>

namespace qsua {

class PjSuaCore : public QObject
{
    Q_OBJECT
public:
    PjSuaCore(QObject *parent = nullptr);

    void onHangupAllCalls();

public slots:
    void onPjsuaStart();
    void onPjsuaDestroy();

private:
    pj::Endpoint pjCore_{};
};

} // namespace qsua

#endif // QSUA_PJSUACORE_H
