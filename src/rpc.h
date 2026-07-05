#pragma once

#include "bus.h"

struct RPC {
    RPC(const Bus &bus);
    const Bus &bus;
};
