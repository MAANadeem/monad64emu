#pragma once

#include "../base.h"
#include <array>

struct RegStatus {
    u32 raw;

    // operating mode enum
    enum MODE { Kernel = 0b00, Supervisor = 0b01, User = 0b10, Invalid = 0b11 };

    // diagnostic status struct
    struct {
        // instruction supervisor_64_bit_addressingce support
        bool instruction_trace_support;
        // exception vector location - 0 -> normal, 1 -> bootstrap
        bool exception_vector;
        // TLB  shutdown
        bool TLB_shutdown;
        // soft reset/NMI occurance
        bool soft_reset;
        // cp0 condition
        bool cp0_condition;
    } diagnostic_status;

    // interupt mask struct
    struct {
        bool timer_interrupt;
        std::array<bool, 5> external_interrupt_write_req;
        std::array<bool, 2> software_interrupt_cause_reg;
    } interrupt_mask;

    std::array<bool, 4> coprocessor_usability;
    bool reduced_power;
    bool floating_point_regs;
    bool reverse_endianness;
    bool kernel_64_bit_addressing;
    bool supervisor_64_bit_addressing;
    bool user_64_bit_addressing;
    MODE mode;
    bool error_level;
    bool exception_level;
    bool interrupt_enable;

    void Write(u32 new_reg);
};

struct RegConfig {
    enum DataTransferPattern { D, DxxDxx, RFU };
    enum Endianness { Little, Big };

    DataTransferPattern data_transfer_pattern;
    Endianness endianness;
    bool cu;
    bool kseg0_cache_enabled;

    void Write(u32 new_reg);
};

struct CP0 {
    CP0();
    void PowerOnReset();
    void WriteToReg(u8 reg_num, u64 new_reg_value);
    RegConfig reg_config;
    RegStatus reg_status;
};
