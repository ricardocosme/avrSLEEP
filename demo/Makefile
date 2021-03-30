mcu=attiny13a
dev=t13
std=c++11
avr_io_inc=../../avrIO/include
avr_int_inc=../../avrINT/include
avr_wdt_inc=../../avrWDT/include

all: power_down_sleep_1s.elf power_down_sleep_15min.elf

%.elf: %.cpp
	avr-g++ -std=$(std) -mmcu=$(mcu) -Os  -o $@ $<  \
	-I../include -I$(avr_io_inc) -I$(avr_int_inc) -I$(avr_wdt_inc)
	avr-size $@

%.s: %.elf
	avr-objdump -d $< > $@
	cat $@

.PHONY: clean flash-%

flash-%: %.elf
	avrdude -p $(dev) -c usbasp -P usb  -U flash:w:$<

clean:
	rm -f *.elf *.s
