#pragma once

#include "INet.h"

#ifdef sn_winnt
#include <winsock2.h> // Header for Windows socket API
#include <ws2tcpip.h> // Header for TCP/IP protocols
#include <stdexcept>  // Header for std::runtime_error
#endif

namespace snet {

    class TcpClient : public INetClient
    {
    public:
        TcpClient();
        virtual ~TcpClient();

        virtual bool open() override;
        virtual bool connect(const char *address, u32 port) override;

        virtual bool send(const u8 *data, u32 size) override;
        virtual bool send(const void *data, u32 size) override;
        virtual int read(u8 *data) override;
        virtual int read(void *data) override;

        virtual bool close() override;
        virtual bool stop() override;

        bool setSocket(socket_ptr ptr);

    protected:
#ifdef sn_unix_base
        int _socket_fd;
#else
        SOCKET socket;
#endif
    };
}