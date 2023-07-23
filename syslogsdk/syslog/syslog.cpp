#include <QString>
#include <QMutexLocker>
#include <QDateTime>

#include "syslog.h"
#include "CLocalClient.h"

#define MAX_LOG_SIZE 1024
#define SERVERNAME "server.syslogd"

static QString print_prefix = QString();
static SYSLOG::SYSLOG_LEVEL_E print_level = SYSLOG::SYSLOG_LEVEL_ALL;
static QMutex print_mutex;
static char print_buffer[MAX_LOG_SIZE] = { 0 };
static bool print_init = false;
static CLocalClient* print_client = nullptr;

void SYSLOG::Create(const char* prefix)
{
    if(!print_init) {
        print_prefix = prefix;
        print_init = true;
        print_client = new CLocalClient;
        print_client->ConnectToServer(SERVERNAME);
        print_client->sendMessage("Hellow Server");
    }
}

void SYSLOG::Destroy(void)
{
    if(print_init) {
        print_prefix = "";
        print_level = SYSLOG::SYSLOG_LEVEL_ALL;
        print_init = false;
        delete print_client;
        print_client = nullptr;
    }
}

void SYSLOG::SetLogLevel(SYSLOG::SYSLOG_LEVEL_E level)
{
    if(print_init) {
        print_level = level;
    }
}

SYSLOG::SYSLOG_LEVEL_E SYSLOG::GetLogLevel(void)
{
    return print_level;
}

int SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_E level, const char* prefix, const char* funcName, const char* fmt, ...)
{
    if(!print_init) {
        return SYSLOG::SYSLOG_ERRCODE_FAIL;
    }

    if(level < print_level) {
        return SYSLOG::SYSLOG_ERRCODE_FAIL;
    }

    QMutexLocker lock(&print_mutex);

    snprintf(print_buffer, sizeof(print_buffer), "[%s][%s]", print_prefix.isEmpty() ? "Unkow" : print_prefix.toStdString().c_str(), prefix);
    snprintf(print_buffer + strlen(print_buffer), MAX_LOG_SIZE - strlen(print_buffer), "[%s]", QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz").toStdString().c_str());
    snprintf(print_buffer + strlen(print_buffer), MAX_LOG_SIZE - strlen(print_buffer), "[%s]", funcName);

    va_list body;
    va_start(body, fmt);
    vsnprintf(print_buffer + strlen(print_buffer), MAX_LOG_SIZE - strlen(print_buffer), fmt, body);
    va_end(body);
    snprintf(print_buffer + strlen(print_buffer), MAX_LOG_SIZE - strlen(print_buffer), "%s", "\n");
    print_client->sendMessage(print_buffer);
    return SYSLOG::SYSLOG_ERRCODE_SUCCESS;
}
