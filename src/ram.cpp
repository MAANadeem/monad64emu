#include "ram.h"

RAM::RAM() { mem_array = std::vector<u16>(RAM_SIZE, 0); }
