#include "LPC23xx.h"

int main(void)
{	int a;
	FIO3DIR = 0xFF;
	FIO4DIR = 0x00;
	while(1)
	{
		a = FIO4PIN;
		FIO3PIN = a^0xFF;
	}
	return 0;
}
