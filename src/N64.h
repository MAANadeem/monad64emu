#include "bus.h"
#include "cpu.h"
#include "ram.h"
#include "rpc.h"

struct N64 {
  N64();
  void Run();
  CPU cpu;
  RAM ram;
  RPC rpc;
  Bus bus;
};
