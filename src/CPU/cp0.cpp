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
        throw "No corresponding cp0 reg";
    }
}

void RegStatus::Write(u32 new_reg) {
    raw = new_reg;
    coprocessor_usability = {
        (new_reg & (1 << 31)) != 0, (new_reg & (1 << 30)) != 0,
        (new_reg & (1 << 29)) != 0, (new_reg & (1 << 28)) != 0};
    reduced_power = (new_reg & (1 << 27)) != 0;
    floating_point_regs = (new_reg & (1 << 26)) != 0;
    reverse_endianness = (new_reg & (1 << 25)) != 0;

    diagnostic_status.instruction_trace_support = (new_reg & (1 << 24)) != 0;
    diagnostic_status.exception_vector = (new_reg & (1 << 22)) != 0;
    diagnostic_status.TLB_shutdown = (new_reg & (1 << 21)) != 0;
    diagnostic_status.soft_reset = (new_reg & (1 << 20)) != 0;
    diagnostic_status.cp0_condition = (new_reg & (1 << 18)) != 0;

    interrupt_mask.timer_interrupt = (new_reg & (1 << 15)) != 0;
    interrupt_mask.external_interrupt_write_req = {
        (new_reg & (1 << 14)) != 0, (new_reg & (1 << 13)) != 0,
        (new_reg & (1 << 12)) != 0, (new_reg & (1 << 11)) != 0,
        (new_reg & (1 << 10)) != 0};
    interrupt_mask.software_interrupt_cause_reg = {(new_reg & (1 << 9)) != 0,
                                                   (new_reg & (1 << 8)) != 0};

    kernel_64_bit_addressing = (new_reg & (1 << 7)) != 0;
    supervisor_64_bit_addressing = (new_reg & (1 << 6)) != 0;
    user_64_bit_addressing = (new_reg & (1 << 5)) != 0;

    u8 raw_mode = (new_reg >> 3) & 0b11;
    mode = static_cast<MODE>(raw_mode);

    error_level = (new_reg & (1 << 2)) != 0;
    exception_level = (new_reg & (1 << 1)) != 0;
    interrupt_enable = (new_reg & (1 << 0)) != 0;
}
