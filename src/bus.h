#pragma once

#include "ram.h"

struct Bus {
    Bus(const MemMap &mem);
    u32 ReadWordPhys(u32 physical_address) const;
    const MemMap &mem;
};
