#pragma once

#include "base.h"
#include <vector>

constexpr u32 RAM_SIZE = 4 * 1024 * 1024; // 4 MB

class MemMap {
  public:
    MemMap(std::vector<u8> pif, std::vector<u8> rom);
    u32 ReadWordPhys(u32 physical_address) const;

  private:
    const std::vector<u8> pif;
    const std::vector<u8> rom;
    std::vector<u8> ram;
};
