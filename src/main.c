#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "hardware.h"

///////////////////////////////////////////////////////////////////////////////

int main();
void init();

///////////////////////////////////////////////////////////////////////////////

int main() {
	init();

	while (true) {
		set_power(0, true);
		set_output(7, true);
		_delay_us(50);
		set_power(0, false);
		set_output(7, false);
		_delay_ms(1);
	}
}

void init() {
	// Enable outputs
	DDRB = 0xFF;
	DDRC = 0x03;
	DDRD = 0xF0;

	sei();
}
