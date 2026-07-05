#include "base.h"

struct CPU;
struct RAM;
struct RPC;

struct Bus {
  Bus(const CPU &cpu, const RAM &ram, const RPC &rpc);
  const CPU &cpu_signal;
  const RAM &ram_signal;
  const RPC &rpc_signal;
};
