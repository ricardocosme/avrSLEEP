#include <avr/io.hpp>
#include <avr/sleep.hpp>

using namespace avr::io;
using namespace avr::sleep;

/** We need to have one ISR to handle WDT interrupts because the MCU
    wakes up through a WDT interrupt. */
AVRINT_WDT(){}

/** 
    This demo illustrates the usage of power_down::sleep<Period>()
    when Period is a timeout value that is equal to some WDT prescaler
    value.
    
    The MCU sleeps for 1s using the power down mode and the watchdog
    timer wakes it up using a watchdog timer interruption.
 */
int main() {
    Pb0 led{output};
    led.low();
    
    while(true) {
        /** Toggle the LED when the MCU wakes up. */
        led.toggle();
        
        power_down::sleep_for<1_s>();
        /** after wake up from the sleep the MCU returns to the
            beginning of loop(next instruction). */
    }
}
