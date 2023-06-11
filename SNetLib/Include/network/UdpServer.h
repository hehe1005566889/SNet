#pragma once

#include "INet.h"

namespace snet {

    class UdpServer : public INetServer 
    {
    public:
        ~UdpServer();
        
    public:
        virtual bool open() override;
        virtual bool listen(const char *address, u32 port) override;

        virtual ref<INetServerConnection> accept_client() override;

        virtual bool stop() override;
        virtual bool close() override;

    private:
    #ifdef sn_unix_base
        int serverSocket = -1;
    #else
        SOCKET serverSocket;
    #endif
    };

}