#include "siplogwriter.h"

#include <QtDebug>

namespace qsua {

SipLogWriter::SipLogWriter()
{

}

void SipLogWriter::write(const pj::LogEntry &entry)
{
    switch(entry.level)
    {
    case 0:
        qFatal("%s %u %s", entry.threadName.c_str(), static_cast<unsigned int>(entry.threadId), entry.msg.c_str());
        break;
    case 1:
        qCritical() << entry.threadName.c_str() << entry.threadId << entry.msg.c_str();
        break;
    case 2:
        qWarning() << entry.threadName.c_str() << entry.threadId << entry.msg.c_str();
        break;
    case 3:
        qInfo() << entry.threadName.c_str() << entry.threadId << entry.msg.c_str();
        break;
    default:
        qDebug() << entry.threadName.c_str() << entry.threadId << entry.msg.c_str();
        break;
    }
}

} // namespace qsua
