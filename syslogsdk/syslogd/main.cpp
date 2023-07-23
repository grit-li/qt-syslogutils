#include <QCoreApplication>
#include "SyslogdCommandLine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationVersion("v1.0");
    SyslogdCommandLine cmd;
    cmd.process(a.arguments());
    return a.exec();
}
