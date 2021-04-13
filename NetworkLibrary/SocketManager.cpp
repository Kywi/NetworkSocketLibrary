#include "pch.h"
#include "SocketManager.h"

using namespace EugeneProduction;
using namespace std;

SocketManager::SocketManager(std::shared_ptr<ISocketFactory> socketFactory)
    : m_socketFactory(socketFactory)
{
}

SocketManager::~SocketManager()
{
    CloseAllConnections();
}

bool SocketManager::IfListens() const
{
    lock_guard<mutex> lock(m_mutex);

    return m_listenerSocket != nullptr;
}

void SocketManager::CreateListenSock(const SOCKADDR_IN& address)
{
    if (m_listenerSocket)
        throw exception("Listener socket is already created");

    m_listenerSocket = m_socketFactory->CreateListenSocket(address);


}

shared_ptr<ISocket> SocketManager::Connect(const SOCKADDR_IN& address)
{
    auto connectedSock = m_socketFactory->CreateConnectionSocket(address);
    m_sockets.push_back(connectedSock);
    return connectedSock;
}

shared_ptr<ISocket> SocketManager::Accept()
{
    auto sock = m_socketFactory->CreateAcceptedConnectionSocket(m_listenerSocket->AcceptConnection());
    m_sockets.push_back(sock);
    return sock;
}

void SocketManager::CloseConnectedSock(shared_ptr<ISocket>& sock)
{
    if (!sock) throw exception("No socket to close");

    lock_guard<mutex> lock(m_mutex);

    auto it = find(m_sockets.begin(), m_sockets.end(), sock);
    if (it != m_sockets.end())
    {
        (*it)->CloseConnection();
        m_sockets.erase(it);
    }
}

void SocketManager::CloseListenSock() const
{
    m_listenerSocket->CloseConnection();
}

void SocketManager::CloseAllConnections()
{
    for (const auto& ref : m_sockets)
        ref->CloseConnection();
    m_sockets.clear();
    if (m_listenerSocket) m_listenerSocket->CloseConnection();
}