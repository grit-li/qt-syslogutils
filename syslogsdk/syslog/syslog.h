#ifndef SYSLOG_H
#define SYSLOG_H

#include <QtCore/qglobal.h>

#if defined(SYSLOG_LIBRARY)
#  define SYSLOG_EXPORT Q_DECL_EXPORT
#else
#  define SYSLOG_EXPORT Q_DECL_IMPORT
#endif

class SYSLOG_EXPORT SYSLOG
{
public:
    enum SYSLOG_LEVEL_E
    {
        SYSLOG_LEVEL_ALL = 0,   ///< all log
        SYSLOG_LEVEL_DEBUG,     ///< debug log
        SYSLOG_LEVEL_INFO,      ///< info log
        SYSLOG_LEVEL_WARN,      ///< warn log
        SYSLOG_LEVEL_ERROR,     ///< error log
        SYSLOG_LEVEL_FATAL,     ///< fatal log
        SYSLOG_LEVEL_OFF        ///< no log
    };

    enum SYSLOG_ERRCODE_E
    {
        SYSLOG_ERRCODE_SUCCESS =  0,
        SYSLOG_ERRCODE_FAIL    = -1,
    };

public:
    static void Create(const char*);
    static void Destroy(void);

    static void SetLogLevel(enum SYSLOG_LEVEL_E);
    static enum SYSLOG_LEVEL_E GetLogLevel(void);

public:
    static int LOG(enum SYSLOG_LEVEL_E, const char*, const char*, const char*, ...);
};

#define LOGD(fmt, ...) SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_DEBUG, "DEBUG", __FUNCTION__, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_INFO, "INFO", __FUNCTION__, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_WARN, "WARN", __FUNCTION__, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_ERROR, "ERROR", __FUNCTION__, fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) SYSLOG::LOG(SYSLOG::SYSLOG_LEVEL_FATAL, "FATAL", __FUNCTION__, fmt, ##__VA_ARGS__)

#define LOGIN()   LOGI("+++[IN]+++");
#define LOGOUT()  LOGI("---[OUT]---");

#endif // SYSLOG_H
