#include "SyslogdCommandLineProcess.h"
#include <QDebug>

SyslogdCommandLineProcess::SyslogdCommandLineProcess(void)
    : m_Server(nullptr)
    , m_buffSize(500)
    , m_outputTarget(SyslogdOutputTarget_qDebug)
{
}

SyslogdCommandLineProcess::~SyslogdCommandLineProcess(void)
{
    if(m_Server) {
        delete m_Server;
    }
}

void SyslogdCommandLineProcess::SetSyslogdBufferSize(uint size)
{
    m_buffSize = size;
}

void SyslogdCommandLineProcess::SetSyslogdOutputTarget(const QString& target)
{
    if(target == "qDebug") {
        m_outputTarget = SyslogdOutputTarget_qDebug;
    } else if(target == "logcat") {
        m_outputTarget = SyslogdOutputTarget_logcat;
    }
}

int SyslogdCommandLineProcess::exec(void)
{
    if(m_Server) {
        return SyslogdCommandLineProcessErrorCode_Success;
    }
    m_Server = new CLocalServer;
    QObject::connect(m_Server, SIGNAL(SendMessage(const QString&)), this, SLOT(ReceiveMessage(const QString&)));
    m_Server->RunServer();
    return SyslogdCommandLineProcessErrorCode_Success;
}

void SyslogdCommandLineProcess::ReceiveMessage(const QString& message)
{
    qDebug("%s", message.toStdString().c_str());
}

