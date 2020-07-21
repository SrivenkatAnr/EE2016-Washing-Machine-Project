	TTL factorial
	AREA Program, CODE, READONLY
	ENTRY
	
MAIN
	;LDR R1, Value1
	;LDR R2, Value2
	ADD R1, R1, #0004 ;4 Factorial
	ADD R2, R2, #0001
Loop
	MUL R3, R2, R1
	MOV R2, R3
	SUBS R1, R1, #0x1
	BNE Loop			; R3 contains the final result

						
	SWI &11
	
;Value1 DCD &0005
;	ALIGN
;Value2 DCD &0001
;	ALIGN

	END