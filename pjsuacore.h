#ifndef QSUA_PJSUACORE_H
#define QSUA_PJSUACORE_H

#include "sipaccount.h"

#include <pjsua2.hpp>
#include <QObject>
#include <QThread>

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
    void onCreateAccount();
    void onMakeCall(const QString& uri);

signals:
    void regStateChanged(bool regIsActive, QString statusTxt);
    void incomingCall(qsua::SipCall* call);
    void newCall(qsua::SipCall* call);

private:
    void makeCallWorker(const QString& uri);
    void createAccountWorker();

    QThread* callThread_{};
    pj_thread_t* pjCallThread_{};
    pj_thread_desc* pjCallThreadDesc_{};
    QThread* createAccountThread_{};
    pj_thread_t* pjCreateAccountThread_{};
    pj_thread_desc* pjCreateCreateAccountThreadDesc_{};

    pj::Endpoint pjCore_{};
    SipAccount *account_{};
};

} // namespace qsua

#endif // QSUA_PJSUACORE_H
