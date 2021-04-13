#include "pch.h"
#include "Socket.h"

#include "NetworkConstants.h"

using namespace EugeneProduction;
using namespace std;

Socket::Socket(ConnectionInfo info) : m_info(info)
{
}

Socket::~Socket()
{
    Socket::CloseConnection();
}

bool Socket::IsConnected()
{
    const int sendBytes = send(m_info.socketConnection, NULL, 0, 0);
    return  sendBytes != SOCKET_ERROR;
}


void Socket::SendData(std::string data)
{
    const int bufSize = NetworkConstants::BufferSize;
    char buffer[bufSize];
    ZeroMemory(buffer, bufSize);
    strcpy_s(buffer, data.c_str());
    if (send(m_info.socketConnection, buffer, sizeof(buffer), NULL) == SOCKET_ERROR)
        throw exception("Can`t send message");
}

string Socket::ReceiveData()
{
    const int bufSize = NetworkConstants::BufferSize;
    char buffer[bufSize];
    ZeroMemory(buffer, bufSize);
    if (recv(m_info.socketConnection, buffer, bufSize, NULL) == SOCKET_ERROR)
        throw exception("Can`t receive message");

    return string(buffer);
}

SOCKADDR_IN Socket::GetSockAddr()
{
    return m_info.m_address;
}

void Socket::CloseConnection()
{
    closesocket(m_info.socketConnection);
}

