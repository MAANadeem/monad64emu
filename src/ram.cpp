#include "ram.h"

MemMap::MemMap(std::vector<u8> pif, std::vector<u8> rom)
    : pif(pif), rom(rom), ram(RAM_SIZE, 0) {}
