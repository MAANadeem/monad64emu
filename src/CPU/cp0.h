#pragma once

struct RegConfig {
    enum Ep { D, DxxDxx, RFU };
    enum Be { LittleEndian, BigEndian };
    Ep ep;
    Be be;
};

struct RegStatus {
    // diagnostic status struct
    struct DS {
        // instruction trace support
        bool its;
        // exception vector location - 0 -> normal, 1 -> bootstrap
        bool bev;
        // TBL shutdown
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
    // coprocessor useability
    bool cu[4];
    // reduced power
    bool rp;
    // additional floating point regs enable
    bool fr;
    // reverse endianess
    bool re;
    // diagnostic status
    DS ds;
    // interupt mask
    IM im;
    // kernel mode 64 bit addressing
    bool kx;
    // supervisor mode 64 bit addressing
    bool sx;
    // user mode 64 bit addressing
    bool ux;
    // operating mode
    MODE mode;
    // error level
    bool erl;
    // exception level
    bool exl;
    // interupt enable
    bool ie;
};

struct CP0 {
    CP0();
    void PowerOnReset();
    RegConfig reg_config;
    RegStatus reg_status;
};
