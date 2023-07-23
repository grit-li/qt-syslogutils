#ifndef SYSLOGD_CSERVER_H
#define SYSLOGD_CSERVER_H

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>

class CLocalServer : public QObject
{
    Q_OBJECT
public:
    CLocalServer(void);
    ~CLocalServer(void);
public:
    void RunServer(void);

private slots:
    void serverNewConnectionHandler(void);
    void socketReadyReadHandler(void);

signals:
    void SendMessage(const QString&);

private:
    QLocalServer* m_server;
};

#endif
