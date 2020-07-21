#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#define F_CPU 8000000

int load= 0x01 ; // Variable for storing Load type input
int task= 0x01 ; // Variable for storing Task type input 
int flag = 0; // Interrupt setting variable

void select();
void setup();
void wash(int);
void dry(int);
void blink(int);
void buzzer();

void blink(int i)
{
             // PRESCALER = 64s
	for(int k=0;k<(2*i);k++)
	{
		for(int j=0;j<250;j++)
		{
			TCCR0 = (1<<CS01)|(1<<CS00);
			TCNT0 = 0x06;
			while( (TIFR & (1<<TOV0)) == 0)
			{
				if(flag==0){select();}
			}
			TCCR0=0;
TIFR = (1<<TOV0);
		}
	}
	
}

void wash(int load2)
{
	if(load2==0x04)
		{load2-=0x01;}
		
	for(int i=0; i<((load2*2)+1);i++)
	{
		PORTB |= (1<<PB6); // Using PB6 for red LEDs
		blink(2);
		PORTB ^= 0x40;
		blink(2);
	}
}

void dry(int load2)
{
	if(load2==0x04)
		{load2-=0x01;}
	
	PORTB |= (1<<PB6);
	blink(load2*4);
	PORTB ^= 0x40;
}

void buzzer()
{
	PORTB |= (1<<PB7);
	PORTB &= 0xB8;
	blink(2);
	PORTB &= 0x38 ;
}

void setup()
{
	PORTB &= 0xF8;
	PORTB |= load; // (written for PB0 PB1 PB2)
	
	if(task == 0x01) // Task 0x01 for wash and dry
	{
		wash(load);
		dry(load); 
		buzzer();
	}
	if(task == 0x02) //Washing only
	{
		wash(load);
		buzzer();
	}
	if(task == 0x04) //Drying only
	{
		dry(load);
		buzzer();
	}
	
}

void select()
{
	GICR = 0x40; //Disabling INT1
	DDRB = 0b11111111;  //Green - PB0, Yellow - PB1, Blue - PB2, Red - PB6, Buzzer - PB7
	DDRC = 0x00;	// Taking inputs LSB 6 bits
	DDRD = 0b11110011; //Interrupt inputs
	
	//PORTB = 0b00111000;
	//PORTC = 0b00111111;
	//PORTD = 0b00001100;
	
	load =0x00;task=0x00;
	PORTB &=0x38; //Ensuring that the LEDs and buzzers are ‘off’ before starting the process
	while(1)
	{											 
if ((((~PINC)&(0x07))==0x01)||(((~PINC)&(0x07))==0x02)||(((~PINC)&(0x07))==0x04))							 // Taking only valid inputs
		{
			load = (~PINC)&(0x07);
		}
		if ((((~PINC)&(0x38))==0x08)||(((~PINC)&(0x38))==0x10)||(((~PINC)&(0x38))==0x20))							// taking only valid inputs
		{
			task = (((~PINC)&(0x38))>>3) ; //LSB 3 bits empty in task and now shifted								
		}
		if (((~PIND)&(0x08))==0x08 && (load!=0x00) && (task!=0x00)) // using int1 for start
		{
			flag=1;
			GICR = 0xC0; //Enabling both INT0 and INT1
			setup();		}
	}
}

ISR(INT0_vect)
{
	reti();
}

ISR(INT1_vect)
{
	flag = 0;
	GICR ^= 0x80; //disabling INT1
	reti();
}

//MAIN FUNCTION STARTS

// PD2 = INT0 and PD3= INT1

void main()
{
	GICR = 0x40; //INT0 only enabled, INT1 is disabled
	MCUCR = 0x08; //INT0: low level; INT1: falling edge
		
	sei();
	
	while (1)
	{
		select();
	}
	
}
