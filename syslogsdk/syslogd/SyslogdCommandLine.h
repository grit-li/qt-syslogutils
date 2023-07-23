#ifndef SYSLOGD_COMMANDLINE_H
#define SYSLOGD_COMMANDLINE_H

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStringList>
#include "SyslogdCommandLineProcess.h"

class SyslogdCommandLine : public QCommandLineParser, public SyslogdCommandLineProcess
{
public:
    SyslogdCommandLine(void);

    int process(const QStringList&);

    static inline int exec(const QStringList&);
};

inline int SyslogdCommandLine::exec(const QStringList& arguments)
{
    SyslogdCommandLine cmd;
    return cmd.process(arguments);
}

#endif
