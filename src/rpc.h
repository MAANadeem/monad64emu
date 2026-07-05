#pragma once

#include "memmap.h"

struct RPC {
    RPC(const MemMap &mem);
    const MemMap &mem;
};
