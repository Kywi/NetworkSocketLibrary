#pragma once

#include "ISocketListen.h"
#include "ConnectionInfo.h"

namespace EugeneProduction
{
    class ListenTCPSock : public ISocketListen
    {
    public:
        explicit ListenTCPSock(ConnectionInfo info);
        ~ListenTCPSock();

        bool IsConnected() override;
        std::string ReceiveData() override;
        void SendData(std::string data) override;
        ConnectionInfo AcceptConnection() override;
        SOCKADDR_IN GetSockAddr() override;
        void CloseConnection() override;

    private:
        ConnectionInfo m_info;
    };
}