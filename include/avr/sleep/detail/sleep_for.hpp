#pragma once

#include "avr/sleep/mcu.hpp"

#include <avr/interrupt.hpp>

namespace avr { namespace sleep { namespace power_down { namespace detail {

inline void sleep_for(uint32_t period) {
    mcu::turn_on_wdt(period);
    interrupt::on();
    mcu::pwd::on();
    asm("sleep");
}

}}}}
