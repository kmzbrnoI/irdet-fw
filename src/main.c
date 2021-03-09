#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "hardware.h"

///////////////////////////////////////////////////////////////////////////////

int main();
void init();
bool read_pin(size_t pini);

///////////////////////////////////////////////////////////////////////////////

int main() {
	size_t pwri = 0;
	bool error = false;
	init();

	// Cycling through all IR's takes ~1.5 ms
	while (true) {
		// Single loop ~350 us

		set_power(pwri, true);
		_delay_us(40);

		bool pina1 = read_pin(pwri*2);
		bool pinb1 = read_pin(pwri*2+1);
		set_power(pwri, false);

		_delay_us(200);

		bool pina2 = read_pin(pwri*2);
		bool pinb2 = read_pin(pwri*2+1);

		set_output(2*pwri, (pina1 && !pina2));
		set_output(2*pwri+1, (pinb1 && !pinb2));

		if (pina2 || pinb2)
			error = true;

		pwri++;
		if (pwri >= POWER_OUTPUTS) {
			pwri = 0;
			status_led(error);
			error = false;
		}
	}
}

void init() {
	// Configure outputs
	DDRB = 0xFF;
	DDRC = 0x03;
	DDRD = 0xF0;

	status_led(true);
	_delay_ms(200);
	status_led(false);
}

bool read_pin(size_t pini) {
	// Takes ~15us at -O3
	static const size_t NO_READS = 12;
	static const size_t THRESHOLD = 8;
	size_t counter = 0;
	for (size_t i = 0; i < NO_READS; i++) {
		if (!get_input(pini))
			counter++;
		_delay_us(1);
	}
	return (counter >= THRESHOLD);
}
