#include "memmap.h"

MemMap::MemMap(std::vector<u8> pif, std::vector<u8> rom)
    : pif(pif), rom(rom), ram(RAM_SIZE, 0) {}

u32 MemMap::ReadWordPhys(u32 physical_address) const {
    if (physical_address >= 0x1fc00000 && physical_address < 0x1fc007c0) {
        u32 relative_address = physical_address - 0x1fc00000;
        u32 built_opcode = pif[relative_address] << 24;
        built_opcode |= pif[relative_address + 1] << 16;
        built_opcode |= pif[relative_address + 2] << 8;
        built_opcode |= pif[relative_address + 3];
        return built_opcode;
    } else {
        return -1;
    }
}
