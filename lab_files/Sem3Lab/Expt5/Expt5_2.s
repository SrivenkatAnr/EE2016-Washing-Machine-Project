
	TTL Expt5_2
	AREA Program, CODE, READONLY
	ENTRY
	
Main
	LDR R2, LIST	; Loading the value ( Here 0x12345678 )
	
	AND R3, R2, #&f	
	AND R4, R2, #&f00
	AND R5, R2, #&f0000
	AND R6, R2, #&f000000

	ADD R7, R7, R3
	ADD R7, R7, R4, LSR #4
	ADD R7, R7, R5, LSR #8
	ADD R7, R7, R6, LSR #12
	
	MOV R8,R7, LSL #16 ;Final Value of the result
	
	;STR R7, RESULT
	SWI &11
	
LIST DCW &5678, &1234
;RESULT DCW 0

	END