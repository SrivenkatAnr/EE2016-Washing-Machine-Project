	TTL Expt6-2
	
STX EQU 0x02
ETX EQU 0x03
	
	AREA Program, CODE, READONLY
	ENTRY
	
Main
	ADR R0, string

Loop 
	LDRB R2, [R0], #1
	CMP R2, #ETX
	BEQ Final
	ADD R1, R1, #1
	B Loop

Final
	SUB R1, R1, #1
	SWI &11

string DCB STX,"Hello World", ETX
	  ALIGN

	AREA DataRAM, DATA, READWRITE

	END