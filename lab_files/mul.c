#include "LPC23xx.h"

int main(void)
{
	int a,b;
	FIO3DIR = 0xFF;
	FIO4DIR = 0x00;
	while(1)
	{
		a = FIO4PIN^0xFF;
		b = a%16;
		a = a/16;
		FIO3PIN = a;
	}
 return 0;
}
