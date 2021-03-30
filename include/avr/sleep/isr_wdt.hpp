#pragma once

#include <stdint.h>

#ifndef AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION
#define AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION 8
#endif

namespace avr { namespace sleep {

/** Software counter used when the sleep period is not equal to some
    WDT prescaler value. 
    
    By the default the resolution of the counter is 8bits, but this can
    be changed to 16bits when needed by a value 16 to the macro
    AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION. There is a compile-time
    assert to warning this when needed.
*/
#if (AVR_SLEEP_WATCHDOG_COUNTER_RESOLUTION == 8)
[[gnu::section(".noinit")]] uint8_t watchdog_cnt;
#else
[[gnu::section(".noinit")]] uint16_t watchdog_cnt;
#endif

/** Increment the software counter. 

    This only should be called inside an AVRINT_WDT() and it **must
    be** called when the software counter is being used.
*/
[[gnu::always_inline]] inline void inc_wdt_cnt()
{ ++watchdog_cnt; }

}}
