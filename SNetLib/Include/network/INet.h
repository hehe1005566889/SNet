#pragma once

#include "NetCommon.h"

namespace snet {

    class sn_api INetClient {
    public:
        virtual bool open() = 0;
        virtual bool connect(const char* address, u32 port) = 0;

        virtual bool send(const u8 *data, u32 size) = 0;
        virtual bool send(const void *data, u32 size) = 0;
        virtual int read(u8* data) = 0;
        virtual int read(void* data) = 0;

        virtual bool close() = 0;
        virtual bool stop() = 0;

    public:
        static ref<INetClient> create(ConnectionType type);

    };

    class sn_api INetServerConnection : public INetClient
    {
    public:
        virtual bool accept(socket_ptr ptr) = 0;
    };

    class sn_api INetServer
    {
    public:
        virtual bool open() = 0;
        virtual bool listen(const char* address, u32 port) = 0;

        virtual ref<INetServerConnection> accept_client() = 0;

        virtual bool stop() = 0;
        virtual bool close() = 0;

    public:
        static ref<INetServer> create(ConnectionType type);
    };
}