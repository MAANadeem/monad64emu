#include "bus.h"
#include "ram.h"
#include <iostream>
Bus::Bus(const MemMap &mem) : mem(mem) {}

u32 Bus::ReadWordPhys(u32 physical_address) const {
    std::cout << 0x1fc00000 << std::endl;
    std::cout << 0x1fc007c0 << std::endl;
    std::cout << physical_address << std::endl;
    if (physical_address >= 0x1fc00000 && physical_address < 0x1fc007c0) {
        u32 relative_address = physical_address - 0x1fc00000;
        std::cout << relative_address << std::endl;
        u32 built_opcode = mem.pif[relative_address] << 24;
        built_opcode |= mem.pif[relative_address + 1] << 16;
        built_opcode |= mem.pif[relative_address + 2] << 8;
        built_opcode |= mem.pif[relative_address + 3];
        return built_opcode;
    } else {
        return -1;
    }
}
