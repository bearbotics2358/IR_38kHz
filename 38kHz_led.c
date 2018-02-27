/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Simple AVR demonstration.  Controls a LED that can be directly
 * connected from OC1/OC1A to GND.  The brightness of the LED is
 * controlled with the PWM.  After each period of the PWM, the PWM
 * value is either incremented or decremented, that's all.
 *
 * $Id: demo.c 1637 2008-03-17 21:49:41Z joerg_wunsch $
 */

#define F_CPU 8000000

#include <inttypes.h>
#include <avr/io.h>
#include <avr/sleep.h>

// yielded 36.7 kHz on 1MHz clock
// and opf course now that I returned to this setting after multiple
// iterations, it measures 38.0 kHz!
#define IR_CLOCK_RATE    38000L
// yielded 39.7 kHz w/1MHz clock
// yielded 38.0 kHz w/8MHz clock, but not as sensitive on detector
// #define IR_CLOCK_RATE    39500L

void init(void)
{
	// use PB0 as output (pin 5)
	DDRB = 0x01;
  // toggle pin 5 on compare
  TCCR0A = _BV(WGM01) | _BV(COM0A0);
  TCCR0B = _BV(CS00);
  
  // 38kHz timer
  OCR0A = (F_CPU/(IR_CLOCK_RATE*2L)-1);
}

int main(void)
{
	init();

	// output is automatic off of timer, so just sleep
	for(;;)
		sleep_mode();

	return(0);
}
