#include "cpu.h"

CPU::CPU(const MemMap &mem)
    : GPR{}, FPR{}, PC{}, HI{}, LO{}, LLBit{}, FCR0{}, FCR31{}, mem(mem) {}

void CPU::PowerOnReset() {
    cp0.PowerOnReset();
    PC = 0xffffffffbfc00000 - 4; // TODO: make this a constant
}

void CPU::Run() {
    PowerOnReset();
    for (;;) {
        PC += 4;
        u32 instruction = ReadWord(PC);
        DecodeAndExecute(instruction);
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
