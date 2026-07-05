#include "N64.h"

N64::N64(std::vector<u8> pif, std::vector<u8> game_binary)
    : mem(pif, game_binary), cpu(mem), rpc(mem) {}

void N64::Run() {
    cpu.PowerOnReset();
    cpu.Run();
}
