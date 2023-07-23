#include "CLocalClient.h"

CLocalClient::CLocalClient(void)
    : m_socket(nullptr)
    , m_timer(nullptr)
    , m_serverName()
{
    m_socket = new QLocalSocket();

    connect(m_socket, SIGNAL(connected()), SLOT(socketConnectedHandler()));
    connect(m_socket, SIGNAL(disconnected()), SLOT(socketDisConnectedHandler()));
    connect(m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), SLOT(socketErrorHandler(QLocalSocket::LocalSocketError)));

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(socketKeepAlive()));
    m_timer->start(1000);
}

CLocalClient::~CLocalClient(void)
{
    m_socket->disconnectFromServer();
    delete m_socket;
    delete m_timer;
}

void CLocalClient::ConnectToServer(const QString &strServerName)
{
    m_serverName = strServerName;
    m_socket->connectToServer(strServerName);
    m_socket->waitForConnected();
}

void CLocalClient::sendMessage(const QString &msg)
{
    if(m_socket->isOpen()) {
        m_socket->write(msg.toStdString().c_str());
        m_socket->flush();
    }
}

void CLocalClient::socketConnectedHandler(void)
{
    qDebug() << "connected.";
    m_timer->stop();
}

void CLocalClient::socketDisConnectedHandler(void)
{
    qDebug() << "disconnected.";
    m_timer->start();
}

void CLocalClient::socketErrorHandler(QLocalSocket::LocalSocketError error)
{
    qWarning() << error;
}

void CLocalClient::socketKeepAlive(void)
{
    qDebug() << "socketKeepAlive" << endl;
    m_socket->connectToServer(m_serverName);
    m_socket->waitForConnected();
}

