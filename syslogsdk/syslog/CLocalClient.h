#ifndef SYSLOGD_CLOCALCLIENT_H
#define SYSLOGD_CLOCALCLIENT_H

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>
#include <QTimer>

class CLocalClient : public QObject
{
    Q_OBJECT

public:
    CLocalClient(void);
    ~CLocalClient(void);

public:
    void ConnectToServer(const QString& strServerName);
    void sendMessage(const QString& msg);

private slots:
    void socketConnectedHandler(void);
    void socketDisConnectedHandler(void);
    void socketErrorHandler(QLocalSocket::LocalSocketError error);
    void socketKeepAlive(void);

private:
    QLocalSocket *m_socket;
    QTimer* m_timer;
    QString m_serverName;
};

#endif
