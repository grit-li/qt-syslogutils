#include "CLocalServer.h"

#define SERVERNAME "server.syslogd"

CLocalServer::CLocalServer(void)
    : QObject(nullptr)
    , m_server(nullptr)
{
    m_server = new QLocalServer;
    connect(m_server, SIGNAL(newConnection()), SLOT(serverNewConnectionHandler()));
}

CLocalServer::~CLocalServer(void)
{
    m_server->close();
    delete m_server;
}

void CLocalServer::RunServer(void)
{
    QLocalServer::removeServer(SERVERNAME);
    m_server->listen(SERVERNAME);
}

void CLocalServer::serverNewConnectionHandler(void)
{
    QLocalSocket* socket = m_server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
}

void CLocalServer::socketReadyReadHandler(void)
{
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if(socket) {
        QTextStream stream(socket);
        emit SendMessage(stream.readAll());
    }
}

