#include "SyslogdCommandLine.h"
#include <QDebug>

static inline QCommandLineOption SetPrintBufferSize(void)
{
    return QCommandLineOption(QStringList() << "C", "Set Print Buffer Size, default 500K", "500");
}

static inline QCommandLineOption SetPrintOutputTarget(void)
{
    return QCommandLineOption(QStringList() << "P" << "Print", "Set Print Output Target, qDebug/logcat", "qDebug");
}

SyslogdCommandLine::SyslogdCommandLine(void)
    : QCommandLineParser()
    , SyslogdCommandLineProcess()
{
    setApplicationDescription("Syslogd Tools");
    addHelpOption();
    addVersionOption();
    addOption(SetPrintBufferSize());
    addOption(SetPrintOutputTarget());
}

int SyslogdCommandLine::process(const QStringList& args)
{
    QCommandLineParser::process(args);
    if(isSet(SetPrintBufferSize())) {
        bool ok;
        uint buffSize = value(SetPrintBufferSize()).toUInt(&ok);
        if(ok) {
            SetSyslogdBufferSize(buffSize);
        }
    }
    if(isSet(SetPrintOutputTarget())) {
        SetSyslogdOutputTarget(value(SetPrintOutputTarget()));
    }
    return SyslogdCommandLineProcess::exec();
}

