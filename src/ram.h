#pragma once

#include "base.h"
#include <vector>

constexpr u32 RAM_SIZE = 4 * 1024 * 1024; // 4 MB

struct MemMap {
    MemMap(std::vector<u8> pif, std::vector<u8> rom);
    std::vector<u8> pif;
    std::vector<u8> rom;
    std::vector<u8> ram;
};
