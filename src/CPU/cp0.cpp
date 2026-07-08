#include "cp0.h"

CP0::CP0() {}

void CP0::PowerOnReset() {
    reg_config.ep = RegConfig::Ep::D;
    reg_config.be = RegConfig::Be::BigEndian;
}
