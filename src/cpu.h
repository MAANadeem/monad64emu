#pragma once

#include "base.h"
#include "memmap.h"
constexpr u8 NUM_GPR = 32;
constexpr u8 NUM_FPR = 32;

struct RegConfig {
    enum RegConfigEp { D, DxxDxx, RFU };
    enum RegConfigBe { LittleEndian, BigEndian };
    RegConfigEp Ep;
    RegConfigBe Be;
};

struct CP0 {
    CP0();
    void PowerOnReset();
    RegConfig reg_config;
};

class CPU {
  public:
    CPU(const MemMap &mem);
    void PowerOnReset();
    void Run();

    u32 ReadWord(u64 address);
    u64 VirtualAddressToPhysicalAddress(u64 virtual_address);

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
