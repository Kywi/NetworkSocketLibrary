#include "pch.h"
#include "ListenTCPSock.h"

#include "NetworkConstants.h"

using namespace EugeneProduction;
using namespace  std;

ListenTCPSock::ListenTCPSock(ConnectionInfo info) : m_info(info)
{
}

void ListenTCPSock::CloseConnection()
{
    closesocket(m_info.socketConnection);
}

SOCKADDR_IN ListenTCPSock::GetSockAddr()
{
    return m_info.m_address;
}

ListenTCPSock::~ListenTCPSock()
{
    ListenTCPSock::CloseConnection();
}

bool ListenTCPSock::IsConnected()
{
    const int sendBytes = send(m_info.socketConnection, NULL, 0, 0);
    return  sendBytes != SOCKET_ERROR;
}

ConnectionInfo ListenTCPSock::AcceptConnection()
{
    SOCKADDR_IN address;
    int addressSize = sizeof(address);
    const auto socket = accept(m_info.socketConnection, reinterpret_cast<SOCKADDR*>(&address), &addressSize);
    if (socket == INVALID_SOCKET)
        throw exception("Error while accepting connection");

    const ConnectionInfo connectedSock
    {
        socket,
        address
    };
    return connectedSock;
}

void ListenTCPSock::SendData(std::string data)
{
    const int bufSize = NetworkConstants::BufferSize;
    char buffer[bufSize];
    ZeroMemory(buffer, bufSize);
    strcpy_s(buffer, data.c_str());
    if (send(m_info.socketConnection, buffer, sizeof(buffer), NULL) == SOCKET_ERROR)
        throw exception("Can`t send message");

}

string ListenTCPSock::ReceiveData()
{
    const int bufSize = NetworkConstants::BufferSize;
    char buffer[bufSize];
    ZeroMemory(buffer, bufSize);
    if (recv(m_info.socketConnection, buffer, bufSize, NULL) == SOCKET_ERROR)
        throw exception("Can`t receive message");

    return string(buffer);
}
