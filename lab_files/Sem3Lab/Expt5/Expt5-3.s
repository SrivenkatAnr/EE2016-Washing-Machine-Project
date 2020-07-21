
	TTL Expt5_3
	AREA Program, CODE, READONLY
	ENTRY
	
Main
	AND R3, R3, #0
	ADD R3, R3, #213
	AND R3, R3, #0001
	SUBS R3, R3, #0001
	BNE Even
	ADD R4, R4, #0001 ; R4 is 1 if odd and R4 is 0 if even
Even
	
	SWI &11
	
	END