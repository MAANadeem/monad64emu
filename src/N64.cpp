#include "N64.h"
#include <iostream>
N64::N64() : cpu(), ram(), rpc(), bus(cpu, ram, rpc) {}

void N64::Run() {
  cpu.PowerOnReset();
  std::cout << cpu.cp0.reg_config.Ep << std::endl;
  std::cout << cpu.cp0.reg_config.Be << std::endl;
}
