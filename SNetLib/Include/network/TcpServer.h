#pragma once

#include "INet.h"
#include "TcpClient.h"

namespace snet {

    class TcpServer : public INetServer {
    public:
        TcpServer();
        virtual ~TcpServer();

        virtual bool open() override;
        virtual bool listen(const char *address, u32 port) override;

        virtual ref<INetServerConnection> accept_client() override;

        virtual bool stop() override;
        virtual bool close() override;

    private:
        int serverSocket = -1;
        bool isListening = false;
    };

    class TcpServerConnection : public INetServerConnection
    {
    public:
        virtual ~TcpServerConnection() 
        {}

        virtual bool open() override 
        { throw std::runtime_error("can't do this action"); return false; }
        virtual bool connect(const char *address, u32 port) override 
        { throw std::runtime_error("can't do this action"); return false; }

        virtual bool send(const u8 *data, u32 size) override 
        { return client.send(data, size); }
        virtual bool send(const void *data, u32 size) override
        { return client.send(data, size); }
        virtual int read(u8 *data) override 
        { return client.read(data); }
        virtual int read(void *data) override
        { return client.read(data); }

        virtual bool close() override 
        { return client.close(); }
        virtual bool stop() override 
        { return client.stop(); }

        virtual bool accept(socket_ptr ptr) override;

    private:
        TcpClient client;
    };
}