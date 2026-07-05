#pragma once

#include "cpu.h"
#include "memmap.h"
#include "rpc.h"

constexpr u16 PIF_ROM_SIZE = 2048;

class N64 {
  public:
    N64(std::vector<u8> pif, std::vector<u8> game_binary);
    void Run();

  private:
    MemMap mem;
    CPU cpu;
    RPC rpc;
};
