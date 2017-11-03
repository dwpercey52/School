*Name: Darrell Percey   Date:2/8/17
*Program: The program takes a 24-bit number stored in
*M and multiples it by N an 8-bit number. The product
*is then stored into Prod
	ORG	$00		;Declaring variables
M	FCB	$04,$12,$15
N	FCB	$30
P1	RMB	2
P2	RMB	2
P3	RMB	2
PROD	RMB	4

	ORG	$B600		;Start of program code
	CLRA		;clear register a/bm
	CLRB
*Finds the numbers for P1
	LDAB	N
	LDAA	M+2	;loads LSB
	MUL		;multiples
	STAB	PROD+3	;stores LSB of product
	STAA	P1	;places MSB of P1
*Finds the numbers for P2
	LDAA	M+1	;loads MID of multiplicand
	LDAB	N	;loads multiplier
	MUL		;multiples 
	STD	P2	;stores A/B in P2 variable
*Finds the numbers for P3	
	LDAA	M	;loads MSB of multiplicand
	LDAB	N	;loads multiplier
	MUL		;multiples
	STD	P3	;stores A/B in P3 variable
*Solves for Product MID-L	
	LDAA	P1	;loads P1 MSB to A
	ADDA	P2+1	;adds P2 LSB to A
	STAA	PROD+2	;stores product in MID-L
*Solves for Product MID-H
	LDAA	P2	;loads P2 MSB to A
	ADCA	P3+1	;adds w/ carry P3 LSB
	STAA	PROD+1	;stores product in MID-H
*Solves for Product MSB
	LDAA	P3	;loads P3 MSB to A
	ADCA	#0	;adds w/ carry a 0
	STAA	PROD	;stores product in MSB
*End of Program
	SWI