#include "pjsuacore.h"

#include <QDebug>

#include "siplogwriter.h"

namespace qsua {

PjSuaCore::PjSuaCore(QObject *parent) : QObject(parent)
{

}

void PjSuaCore::onHangupAllCalls()
{
    pjCore_.hangupAllCalls();
}

void PjSuaCore::onPjsuaStart()
{
    if(pjCore_.libGetState() != pjsua_state::PJSUA_STATE_NULL)
    {
        qWarning() << "PjSua lib are initialized! Restart PjSua lib ...";
        pjCore_.libDestroy();
    }

    pjCore_.libCreate();

    pj::EpConfig epCfg{};
    epCfg.logConfig.level = 5;
    epCfg.logConfig.writer = new SipLogWriter();

    epCfg.medConfig.sndClockRate = 0;
    epCfg.medConfig.sndPlayLatency = 80;
    epCfg.medConfig.sndRecLatency = 80;
    epCfg.medConfig.channelCount = 1;
    epCfg.medConfig.threadCnt = 2;
    epCfg.medConfig.quality = 9;
    epCfg.medConfig.hasIoqueue = true;
    epCfg.medConfig.ptime = 80;
    epCfg.medConfig.noVad = true;

    epCfg.medConfig.jbInit = 180;
    epCfg.medConfig.jbMax = 300;
    epCfg.medConfig.jbMaxPre = 180;
    epCfg.medConfig.jbMinPre = 180;

    pjCore_.libInit(epCfg);


    pj::TransportConfig transportCfg{};
    transportCfg.port = 5060;
    try {
        pjCore_.transportCreate(PJSIP_TRANSPORT_UDP, transportCfg);
    }  catch (const pj::Error &err) {
        qWarning() << "Create transport failed" << err.info().c_str();
        return;
    }

    pjCore_.libStart();
    qDebug() << "PjSua lib started!";

    int dev_count = pjmedia_aud_dev_count();
    qDebug() << "Got" << dev_count << "audio devices";
    for (pjmedia_aud_dev_index dev_idx=0; dev_idx < dev_count; ++dev_idx) {
        pjmedia_aud_dev_info info;
        pjmedia_aud_dev_get_info(dev_idx, &info);
        qDebug() << dev_idx << ". " << info.name << "(in=" << info.input_count << "out=" << info.output_count << ")";
    }

    /*pjmedia_aud_dev_info info;
    pj_status_t status = pjmedia_aud_dev_get_info(PJMEDIA_AUD_DEFAULT_CAPTURE_DEV, &info);
    if (status == PJ_SUCCESS) {
        // Enumerate capability bits
        qDebug() << "Device capabilities: ";
        for (unsigned i=0; i<32; ++i) {
            if (info.caps & (1 << i))
                qDebug() << pjmedia_aud_dev_cap_name(info.caps, NULL));
        }
    }*/

    /*pj::AudDevManager& amanager = pjCore_.audDevManager();
    amanager.setCaptureDev(0);
    amanager.setPlaybackDev(0);*/
}



void PjSuaCore::onPjsuaDestroy()
{
    pjCore_.libDestroy();
}

} // namespace qsua
