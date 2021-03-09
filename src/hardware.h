#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>

#define POWER_OUTPUTS 4

static inline bool get_input(size_t i) {
	if (i <= 3) {
		const static size_t mapping[] = {PINC2, PINC3, PINC5, PINC4};
		return PINC & (1 << mapping[i]);
	} else if (i <= 7) {
		const static size_t mapping[] = {PIND1, PIND0, PIND2, PIND3};
		return PIND & (1 << mapping[i-3]);
	}
	return false;
}

static inline void set_output(size_t i, bool state) {
	if (i <= 4) {
		const static size_t mapping[] = {PORTB4, PORTB3, PORTB2, PORTB1, PORTB0};
		if (state)
			PORTB |= (1 << mapping[i]);
		else
			PORTB &= ~(1 << mapping[i]);
	} else if (i <= 7) {
		const static size_t mapping[] = {PORTD7, PORTD6, PORTD5};
		if (state)
			PORTD |= (1 << mapping[i-5]);
		else
			PORTD &= ~(1 << mapping[i-5]);
	}
}

static inline void set_power(size_t i, bool state) {
	if (i == 0) {
		if (state) PORTC |= (1 << PORTC1); else PORTC &= ~(1 << PORTC1);
	} else if (i == 1) {
		if (state) PORTC |= (1 << PORTC0); else PORTC &= ~(1 << PORTC0);
	} else if (i == 2) {
		if (state) PORTD |= (1 << PORTD4); else PORTD &= ~(1 << PORTD4);
	} else if (i == 3) {
		if (state) PORTB |= (1 << PORTB6); else PORTB &= ~(1 << PORTB6);
	}
}

#endif
