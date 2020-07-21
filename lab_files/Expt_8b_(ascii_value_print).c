#include "LPC23xx.h"
void TargetResetInit(void){
	if((PLLSTAT & 0x02000000) > 0){
		PLLCON &= ~0x02;
		PLLFEED = 0xaa;
		PLLFEED = 0x55;
	}
	PLLCON &= ~0x01;
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	SCS &= ~0x10;
	SCS |= 0x20;
	while((SCS & 0x40) == 0);
	CLKSRCSEL = 0x01;
	PLLCFG = (24 << 0)|(1 << 16);
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	PLLCON |= 0x01;
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	CCLKCFG = 3;
	USBCLKCFG = 5;
	while((PLLSTAT & 0x04000000) == 0);
	PCLKSEL0 = 0xaaaaaaaa;
	PCLKSEL1 = 0x22aaa8aa;
	PLLCON |= 0x02;
	PLLFEED = 0xaa;
	PLLFEED = 0x55;
	while((PLLSTAT & 0x02000000) == 0);
	PCLKSEL0 = 0x55555555;
	PCLKSEL1 = 0x55555555;
}

int serial_rx(void){
	while(!(U0LSR & 0x01));
	return U0RBR;
}

void serial_tx(int ch){
	while((U0LSR & 0x20) != 0x20);
	while((U0LSR & 0x20) == 0);
	U0THR = ch;
}

void string_tx(char *a){
	while(*a != '\0'){
		while((U0LSR & 0x20) != 0x20);
		U0THR  = *a;
		a++;
	}
}

int main(){
	unsigned int Fdiv;
	char value;
	FIO3DIR = 0xFF;
	TargetResetInit();
	PINSEL0 = 0x00000050;
	U0LCR = 0x83;
	Fdiv = (72000000/16)/19200;
	U0DLM = Fdiv/256;
	U0DLL = Fdiv%256;
	U0LCR = 0x03;
	while(1){
		value = serial_rx();
		FIO3PIN = value;
	}
	return 0 ;
}
	