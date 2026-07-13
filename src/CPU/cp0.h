#pragma once

#include "../base.h"

struct RegConfig {
    enum Ep { D, DxxDxx, RFU };
    enum Be { LittleEndian, BigEndian };
    Ep ep;
    Be be;
};

union StatusRegisterUnion {
    u32 raw;

    struct {
        u32 coprocessor_usability : 4;
        u32 reduced_power : 1;
        u32 floating_point_regs : 1;
        u32 reverse_endianness : 1;
        u32 diagnostic_status : 5; // TODO: set up representation
        u32 interrupt_mask : 8;    // TODO: set up representation
        u32 kernel_64_bit_addressing : 1;
        u32 supervisor_64_bit_addressing : 1;
        u32 user_64_bit_addressing : 1;
        u32 mode : 2;
        u32 error_level : 1;
        u32 exception_level : 1;
        u32 interrupt_enable : 1;
    } Fields;
};

struct RegStatus {
    // diagnostic status struct
    struct DS {
        // instruction trace support
        bool its;
        // exception vector location - 0 -> normal, 1 -> bootstrap
        bool bev;
        // TLB  shutdown
        bool ts;
        // soft reset/NMI occurance
        bool sr;
        // cp0 condition
        bool ch;
    };
    // interupt mask struct
    struct IM {
        bool timer_interrupt;
        bool external_interrupt_write_req[5];
        bool software_interrupt_cause_reg[2];
    };
    // operating mode enum
    enum MODE { Kernel, Supervisor, User, Invalid };

    StatusRegisterUnion reg_bits;

    void Write(u32 new_reg_status);
};

struct CP0 {
    CP0();
    void PowerOnReset();
    void WriteToReg(u8 reg_num, u32 new_reg_value);
    RegConfig reg_config;
    RegStatus reg_status;
};
