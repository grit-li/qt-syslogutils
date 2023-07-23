#ifndef SYSLOGD_COMMANDLINE_PROCESS_H
#define SYSLOGD_COMMANDLINE_PROCESS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

#include "CLocalServer.h"

class SyslogdCommandLineProcess : public QObject
{
    Q_OBJECT
public:
    enum SyslogdCommandLineProcessErrorCode_e
    {
        SyslogdCommandLineProcessErrorCode_Success = 0,
        SyslogdCommandLineProcessErrorCode_Command_Unknow = -1,
    };

private:
    enum SyslogdOutputTarget_e
    {
        SyslogdOutputTarget_qDebug,
        SyslogdOutputTarget_logcat
    };

public:
    SyslogdCommandLineProcess(void);
    virtual ~SyslogdCommandLineProcess(void);

public:
    void SetSyslogdBufferSize(uint);

    void SetSyslogdOutputTarget(const QString&);

public:
    virtual int exec(void);

protected slots:
    void ReceiveMessage(const QString&);

private:
    CLocalServer* m_Server;
    uint m_buffSize;
    enum SyslogdOutputTarget_e m_outputTarget;
};

#endif
