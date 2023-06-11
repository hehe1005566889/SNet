#pragma once

#include "INet.h"

namespace snet {

    class UdpClient : public INetClient {
    public:
        virtual bool open() override;
        virtual bool connect(const char *address, u32 port) override;

        virtual bool send(const u8 *data, u32 size) override;
        virtual bool send(const void *data, u32 size) override;
        virtual int read(u8 *data) override;
        virtual int read(void *data) override;

        virtual bool close() override;
        virtual bool stop() override;
    };
}