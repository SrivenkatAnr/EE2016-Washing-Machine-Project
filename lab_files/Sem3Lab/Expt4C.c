#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	for(int x=0;x<3;x++)
	{
		PORTB = 0x01;
		_delay_ms(1000);
		PORTB=0x00;
		_delay_ms(1000);
	}
	


	// Write your ISR here to blink the LED 10 times
	// with ON and OFF interval of 1 second each
	
}
int main(void)
{	
	DDRD = 0x00;
	DDRB = 0x01;
	MCUCR |= /*0x12;*/0x3;
	GICR |= /*0x80;*/0x40;
	PORTB = 0x00;
	
	sei();

	while (1)
	{
	}
}