#include "bus.h"

Bus::Bus(const CPU &cpu, const RAM &ram, const RPC &rpc)
    : cpu_signal{cpu}, ram_signal{ram}, rpc_signal{rpc} {}
