#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "syslog.h"

static QString ConvLogLevelToString(enum SYSLOG::SYSLOG_LEVEL_E level)
{
    QString bRet = QString();
    switch(level) {
        case SYSLOG::SYSLOG_LEVEL_ALL:
            bRet = "SYSLOG_LEVEL_ALL";
            break;
        case SYSLOG::SYSLOG_LEVEL_DEBUG:
            bRet = "SYSLOG_LEVEL_DEBUG";
            break;
        case SYSLOG::SYSLOG_LEVEL_INFO:
            bRet = "SYSLOG_LEVEL_INFO";
            break;
        case SYSLOG::SYSLOG_LEVEL_WARN:
            bRet = "SYSLOG_LEVEL_WARN";
            break;
        case SYSLOG::SYSLOG_LEVEL_ERROR:
            bRet = "SYSLOG_LEVEL_ERROR";
            break;
        case SYSLOG::SYSLOG_LEVEL_FATAL:
            bRet = "SYSLOG_LEVEL_FATAL";
            break;
        case SYSLOG::SYSLOG_LEVEL_OFF:
            bRet = "SYSLOG_LEVEL_OFF";
            break;
    }
    return bRet;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(nullptr)
{
    ui->setupUi(this);
    SYSLOG::Create("syslogtest");
    ui->SetLogLevelShow->setText(ConvLogLevelToString(SYSLOG::GetLogLevel()));

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(PrintTestOutput()));
    m_timer->start(1000);
}

MainWindow::~MainWindow(void)
{
    delete ui;
    delete m_timer;
    SYSLOG::Destroy();
}


void MainWindow::on_SetLogLevel_clicked(void)
{
    static int currentLogLevel = SYSLOG::GetLogLevel();

    if(++currentLogLevel > SYSLOG::SYSLOG_LEVEL_OFF) {
        currentLogLevel = SYSLOG::SYSLOG_LEVEL_ALL;
    }
    SYSLOG::SetLogLevel(static_cast<enum SYSLOG::SYSLOG_LEVEL_E>(currentLogLevel));
    ui->SetLogLevelShow->setText(ConvLogLevelToString(SYSLOG::GetLogLevel()));
}

void MainWindow::PrintTestOutput(void)
{
    LOGIN();
    LOGD("PrintTestOutput");
    LOGI("PrintTestOutput");
    LOGW("PrintTestOutput");
    LOGE("PrintTestOutput");
    LOGF("PrintTestOutput");
    LOGOUT();
}
