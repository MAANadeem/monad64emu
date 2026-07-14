#pragma once

#include "../base.h"
#include "../memmap.h"
#include "cp0.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

constexpr u8 NUM_GPR = 32;
constexpr u8 NUM_FPR = 32;

class CPU {
  public:
    CPU(const MemMap &mem);
    void PowerOnReset();
    void Run();

    u32 ReadWord(u64 address);
    u64 VirtualAddressToPhysicalAddress(u64 virtual_address);
    void DecodeAndExecute(u32 instruction);

  private:
    // Coprocessor
    CP0 cp0;

    // Registers
    u64 GPR[NUM_GPR];
    f64 FPR[NUM_FPR];

    u64 PC;

    u64 HI;
    u64 LO;

    bool LLBit;

    f32 FCR0;
    f32 FCR31;

    const MemMap &mem;
};

inline void Panic(u32 address) {
    std::ostringstream ss;
    ss << "Unrecognized virtual address 0x" << std::hex << address;

    throw std::runtime_error(ss.str());
}
