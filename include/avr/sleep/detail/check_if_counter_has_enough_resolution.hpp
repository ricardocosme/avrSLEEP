#pragma once

#include <stdint.h>

namespace avr { namespace sleep { namespace power_down { namespace detail {

template<bool has_8bits_software_counter, uint32_t period, uint32_t prescaler>
struct check_if_counter_has_enough_resolution;

template<uint32_t period, uint32_t prescaler>
struct check_if_counter_has_enough_resolution<true, period, prescaler> {
    static_assert(period / prescaler <= 255,
                  "The period is too high to be used with "
                  "the selected prescaler and an 8bits software counter. "
                  "The macro AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION can "
                  "be defined to 16 to allow an 16bits software counter.");
};

template<uint32_t period, uint32_t prescaler>
struct check_if_counter_has_enough_resolution<false, period, prescaler> {
    static_assert(period / prescaler <= 65536,
                  "The period is too high to be used with "
                  "the selected prescaler.");
};

}}}}
