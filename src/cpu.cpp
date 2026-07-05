#include "cpu.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

inline void Panic(u32 address) {
    std::ostringstream ss;
    ss << "Unrecognized virtual address 0x" << std::hex << address;

    throw std::runtime_error(ss.str());
}

CP0::CP0() {}

void CP0::PowerOnReset() {
    reg_config.Ep = RegConfig::RegConfigEp::D;
    reg_config.Be = RegConfig::RegConfigBe::BigEndian;
}

CPU::CPU(const MemMap &mem)
    : GPR{}, FPR{}, PC{}, HI{}, LO{}, LLBit{}, FCR0{}, FCR31{}, mem(mem) {}

void CPU::PowerOnReset() {
    cp0.PowerOnReset();
    PC = 0xffffffffbfc00000; // TODO: make this a constant
}

void CPU::Run() {
    PowerOnReset();
    for (;;) {
        u32 instruction = ReadWord(PC);
        u8 opcode = (instruction >> 26) & 0b111111;
        if (opcode == 0b001111) {
            std::cout << "LUI works" << std::endl;
        } else {
            Panic(instruction);
        }
        PC += 4;
    }
}

u32 CPU::ReadWord(u64 virtual_address) {
    u64 physical_address = VirtualAddressToPhysicalAddress(virtual_address);
    return mem.ReadWordPhys(physical_address);
}

u64 CPU::VirtualAddressToPhysicalAddress(u64 virtual_address) {
    u8 address_bit_values = (virtual_address >> 29) & 0b111;

    if (address_bit_values == 0b101) {
        return virtual_address - 0xffffffffa0000000;
    } else {
        Panic(virtual_address);
    }
}
