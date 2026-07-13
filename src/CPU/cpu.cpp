#include "cpu.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

inline void Panic(u32 address) {
    std::ostringstream ss;
    ss << "Unrecognized virtual address 0x" << std::hex << address;

    throw std::runtime_error(ss.str());
}

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

void CPU::DecodeAndExecute(u32 instruction) {
    u8 opcode = (instruction >> 26) & 0b111111;
    switch (opcode) {
    // lui
    case 0b001111: {
        u16 imm = instruction & 0xffff;
        u8 rt = (instruction >> 16) & 0b11111;
        std::cout << "Before: " << (int)rt << " : " << GPR[rt] << std::endl;
        GPR[rt] = imm;
        std::cout << "After: " << (int)rt << " : " << GPR[rt] << std::endl;

    } break;
    // c0 operation
    case 0b010000: {
        std::cout << "Reached c0 operation" << std::endl;
        u8 rd = (instruction >> 11) & 0b11111;
        u8 rt = (instruction >> 16) & 0b11111;
        u8 sub_op = (instruction >> 21) & 0b11111;
        if (sub_op == 0b00100) {
            cp0.WriteToReg(rd, GPR[rt]);
        } else {
            Panic(instruction);
        }
    } break;
    default:
        Panic(instruction);
    }
}
