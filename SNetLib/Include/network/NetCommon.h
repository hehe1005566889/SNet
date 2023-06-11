#pragma once

#include "globals.h"

namespace snet {

    enum class ConnectionType
    { TCP, UDP };

    struct socket_ptr
    {
        int socket;
    };
}