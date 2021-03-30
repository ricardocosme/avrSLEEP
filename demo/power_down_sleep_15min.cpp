#include <avr/io.hpp>
#include <avr/sleep.hpp>

using namespace avr::io;
using namespace avr::sleep;

/** We need to have one ISR to handle WDT interrupts because the MCU
    wakes up through a WDT interruption and it's also essential to
    increment the watchdog timer counter **when** using timeout values
    that aren't equal to any watchdog timer prescaler value.
*/
AVRINT_WDT() { inc_wdt_cnt(); }

/** 
    This demo illustrates the usage of power_down::sleep<Period>()
    when Period is a timeout value that isn't equal to any WDT
    prescaler value.
    
    The MCU sleeps for 15min using the power down mode and the
    watchdog timer wakes it up using a watchdog timer interruption.
 */
int main() {
    Pb0 led{output};
    led.low();
    
    while(true) {
        /** Toggle the LED when the MCU wakes up. */
        led.toggle();
        
        power_down::sleep_for<15_min>();
        /** after wake up from the sleep the MCU returns to the
            beginning of loop(next instruction). */
    }
}
