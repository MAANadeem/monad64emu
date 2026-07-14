#include "cpu.h"

enum OPCODE { LUI, C0, ORI, INVALID };

static inline OPCODE ExtractOpcode(u32 instruction) {
    u8 opcode = (instruction >> 26) & 0b111111;
    switch (opcode) {
    case 0b001111:
        return LUI;
    case 0b010000:
        return C0;
    case 0b001101:
        return ORI;
    }
    Panic(instruction);
    return INVALID;
}

void CPU::DecodeAndExecute(u32 instruction) {
    OPCODE op = ExtractOpcode(instruction);
    switch (op) {
    case LUI: {
        u16 imm = instruction & 0xffff;
        u8 rt = (instruction >> 16) & 0b11111;
        std::cout << "LUI: Reg " << (int)rt << ": " << GPR[rt];
        GPR[rt] = imm << 16;
        std::cout << " -> " << GPR[rt] << std::endl;
    } break;
    // c0 operation
    case C0: {
        std::cout << "C0 operation: ";
        u8 rd = (instruction >> 11) & 0b11111;
        u8 rt = (instruction >> 16) & 0b11111;
        u8 sub_op = (instruction >> 21) & 0b11111;
        if (sub_op == 0b00100) {
            std::cout << "MTC0: Reg " << (u32)rd << ": "
                      << (u32)cp0.reg_status.raw;
            cp0.WriteToReg(rd, GPR[rt]);
            std::cout << " -> " << (u32)cp0.reg_status.raw << std::endl;
        } else {
            Panic(instruction);
        }
    } break;
    case ORI: {
        u16 imm = instruction & 0xffff;
        u8 rs = (instruction >> 21) & 0b11111;
        u8 rt = (instruction >> 16) & 0b11111;
        std::cout << "ORI: Reg " << (int)rt << ": " << GPR[rt];
        GPR[rt] = GPR[rs] | (u32)imm;
        std::cout << " -> " << GPR[rt] << std::endl;
    } break;
    default:
        Panic(instruction);
        break;
    }
}
