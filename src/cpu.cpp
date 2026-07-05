#include "cpu.h"

CP0::CP0() {}

void CP0::PowerOnReset() {
  reg_config.Ep = RegConfig::RegConfigEp::D;
  reg_config.Be = RegConfig::RegConfigBe::BigEndian;
}

CPU::CPU() : GPR{}, FPR{}, PC{}, HI{}, LO{}, LLBit{}, FCR0{}, FCR31{} {}

void CPU::PowerOnReset() { cp0.PowerOnReset(); }
