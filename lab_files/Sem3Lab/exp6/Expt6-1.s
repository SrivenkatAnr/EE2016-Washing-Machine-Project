	TTL Expt6-1
	AREA Program, CODE, READONLY
	ENTRY
	
Main
	LDR R0, Value
	MOV R1, #31
	MOV R2, #1
	
Loop
	AND R4, R2, R0, LSR R1
	ADD R2, R5, R4
	SUBS R1, R1, #1
	BNE Loop
	
	AND R4, R0, #1
	ADD R5, R5, R4
	AND R6, R5, #1
	SWI &11
	

Value	DCW &1,&f
		ALIGN
		;DCW &5678
	
	END
		