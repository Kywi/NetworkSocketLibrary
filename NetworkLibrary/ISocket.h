#pragma once
#include <string>

namespace EugeneProduction
{
    class ISocket
    {
    public:
        virtual void SendData(std::string data) = 0;
        virtual std::string ReceiveData() = 0;
        virtual SOCKADDR_IN GetSockAddr() = 0;
        virtual bool IsConnected() = 0;
        virtual void CloseConnection() = 0;
    };
}
