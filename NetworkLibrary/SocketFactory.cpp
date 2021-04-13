#include "pch.h"

#include <memory>

#include "SocketFactory.h"
#include "ListenTCPSock.h"
#include "NetworkConstants.h"
#include "Socket.h"

using namespace EugeneProduction;
using namespace std;

shared_ptr<ISocketListen> SocketFactory::CreateListenSocket(const SOCKADDR_IN& conInfo)
{
    SOCKADDR_IN address = conInfo;
    const int addressSize = sizeof(address);
    const SOCKET sock = socket(AF_INET, NetworkConstants::TCPSocketType, NULL);
    if (sock == SOCKET_ERROR)
        throw exception("Error while creating listen socket");

    if (bind(sock, reinterpret_cast<SOCKADDR*>(&address), addressSize) == SOCKET_ERROR)
        throw exception("ERROR: Can`t bind socket!");

    if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
        throw exception("Error while start listening socket");

    return make_shared<ListenTCPSock>(ConnectionInfo
        {
            sock,
            address
        });
}

shared_ptr<ISocket> SocketFactory::CreateConnectionSocket(const SOCKADDR_IN& conInfo)
{
    SOCKADDR_IN address = conInfo;
    const int addressSize = sizeof(address);
    const SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
    if (sock == SOCKET_ERROR)
        throw exception("Error while creating listen socket");

    if (connect(sock, reinterpret_cast<SOCKADDR*>(&address), addressSize) == SOCKET_ERROR)
        throw exception("Connecting error");

    return make_shared<Socket>(ConnectionInfo
        {
            sock,
            address
        });
}

shared_ptr<ISocket> SocketFactory::CreateAcceptedConnectionSocket(const ConnectionInfo info)
{
    return make_shared<Socket>(info);
}
