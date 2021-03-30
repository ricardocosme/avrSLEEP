#pragma once

#include <avr/io.hpp>
#include <avr/wdt.hpp>

namespace avr { namespace sleep { namespace mcu {

namespace pwd {
[[gnu::always_inline]] inline void on() {
    using namespace avr::io;
    set(se, sm1, sm0(off));
}

[[gnu::always_inline]] inline void off() {
    using namespace avr::io;
    clear(se, sm1, sm0);
}
}//namespace pwd

template<uint32_t Period>
void check_if_period_is_multiple_of_prescaler() {
    static_assert(
        !(Period % 16)   ||
        !(Period % 32)   ||
        !(Period % 64)   ||
        !(Period % 125)  ||
        !(Period % 250)  ||
        !(Period % 500)  ||
        !(Period % 1000) ||
        !(Period % 2000) ||
        !(Period % 4000) ||
        !(Period % 8000),
        "Period should be multiple of 16ms, 32ms, 64ms, 125ms, 500ms, "
        "1s, 2s, 2s or 8s.");
}

inline constexpr bool is_equal_to_prescaler(uint32_t period) {
    return period == 16   || period == 32   || period == 64   ||
           period == 125  || period == 250  || period == 500  ||
           period == 1000 || period == 2000 || period == 4000 ||
           period == 8000;
}

inline constexpr uint32_t prescaler_to(uint32_t period) {
    return (!(period % 8000) && ((period / 8000) > 0))
        ? 8000
        : (!(period % 4000) && ((period / 4000) > 0))
        ? 4000
        : (!(period % 2000) && ((period / 2000) > 0))
        ? 2000
        : (!(period % 1000) && ((period / 1000) > 0))
        ? 1000
        : (!(period % 500) && ((period / 500) > 0))
        ? 500
        : (!(period % 250) && ((period / 250) > 0))
        ? 250
        : (!(period % 125) && ((period / 125) > 0))
        ? 125
        : (!(period % 64) && ((period / 64) > 0))
        ? 64
        : (!(period % 32) && ((period / 32) > 0))
        ? 32
        : 16;
}

inline void turn_on_wdt(uint32_t period) {
    using namespace wdt;
    if(period == 16)
        on(timeout::at_16ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 32)
        on(timeout::at_32ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 64)
        on(timeout::at_64ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 125)
        on(timeout::at_125ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 250)
        on(timeout::at_250ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 500)
        on(timeout::at_500ms, mode::interrupt, atomic_precondition::yes);
    else if(period == 1000)
        on(timeout::at_1s, mode::interrupt, atomic_precondition::yes);
    else if(period == 2000)
        on(timeout::at_2s, mode::interrupt, atomic_precondition::yes);
    else if(period == 4000)
        on(timeout::at_4s, mode::interrupt, atomic_precondition::yes);
    else if(period == 8000)
        on(timeout::at_8s, mode::interrupt, atomic_precondition::yes);
}

}}}
