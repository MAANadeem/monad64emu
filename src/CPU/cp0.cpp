#include "cp0.h"

CP0::CP0() {}

void CP0::PowerOnReset() {
    reg_config.ep = RegConfig::Ep::D;
    reg_config.be = RegConfig::Be::BigEndian;
}

void CP0::WriteToReg(u8 reg_num, u32 new_reg_value) {
    switch (reg_num) {
    // status
    case 12: {
        reg_status.Write(new_reg_value);
    } break;
    default:
        throw;
    }
}

void RegStatus::Write(u32 new_reg_status) { reg_bits.raw = new_reg_status; }
