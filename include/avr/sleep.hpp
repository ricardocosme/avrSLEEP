#pragma once

#include "avr/sleep/chrono/duration.hpp"
#include "avr/sleep/detail/check_if_counter_has_enough_resolution.hpp"
#include "avr/sleep/detail/sleep_for.hpp"
#include "avr/sleep/isr_wdt.hpp"
#include "avr/sleep/mcu.hpp"

#include <avr/interrupt.hpp>
#include <avr/wdt.hpp>

namespace avr { namespace sleep {

/** Put the MCU to sleep. */
[[gnu::always_inline]] inline void sleep() { asm("sleep"); }

/** Functions to use the Power Down sleep mode. */
namespace power_down {

/** Enable the Power Down sleep mode. */
inline void on() { mcu::pwd::on(); }

/** Disable the Power Down sleep mode. */
inline void off() { mcu::pwd::off(); }

/** Sleep for a period of time.

    Put the MCU to sleep and wakes up after a specific period of time
    defined by 'Period'. One watchdog timer interrupt is used to
    wake up the MCU.

    !Important! It's necessary to have one ISR to handle the WDT
     interrupt because without that the MCU can execute the reset
     vector and the program will not return to the instruction after
     the sleep_for.

    The Period is a template parameter because the compiler do some
    static asserts to validate the period value.

    Examples:
      //sleep for 1s
      sleep_for<1_s>();

      //sleep for 125ms
      sleep_for<125_ms>();

      //sleep for 10s using a software counter to help the watchdog timer
      sleep_for<10_s>();
 */
template<uint32_t Period>
inline void sleep_for() {
    interrupt::atomic<> sa;
    //specific to each MCU. Take a look at 'avr/sleep/mcu.hpp'
    //compile-time assert
    mcu::check_if_period_is_multiple_of_prescaler<Period>();
    
    if(mcu::is_equal_to_prescaler(Period)) {
        detail::sleep_for(Period);
    } else { //usage of a software counter when Period != of any WDT prescaler.
        constexpr auto prescaler = mcu::prescaler_to(Period);
        
        //compile-time assert
        detail::check_if_counter_has_enough_resolution
            <AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION == 8, Period, prescaler>{};
        
        watchdog_cnt = 0;
        while(watchdog_cnt < (Period / prescaler))
            detail::sleep_for(prescaler);
    }
    interrupt::off();
    wdt::off(wdt::atomic_precondition::yes);
}

}// namespace power_down

}}
