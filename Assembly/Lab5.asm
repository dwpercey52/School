*Name: Darrell Percey	Date:3/8/17
*Program: Prints an array of size N*M to the screen then flips it
*swapping by row major form. Then it reprints the results to
*the screen for the user to verify.

N		EQU	4 		; Number of matrix rows
M		EQU	5 		; Number of matrix columns
OUTA		EQU	$FFB8 		; Address of OUTA Buffalo subroutine
OUTSTRG		EQU	$FFC7 		; Address of OUTSTRG Buffalo subroutine
OUTLHLF 	EQU 	$FFB2 		; Address of OUTLHLF Buffalo subroutine
OUTRHLF 	EQU	$FFB5		; Address of OUTRHLF Buffalo subroutine
OUTCRLF 	EQU	$FFC4 		; Address of OUTCRLF Buffalo subroutine
OUT1BTY		EQU	$FFBE		; Prints addres of X and a space

		ORG 	$100
holdI		RMB	1
Matrix		FCB 	0,1,2,3,4
		FCB	5,6,7,8,9		; Enter matrix elements here.
		FCB 	10,11,12,13,14
		FCB	15,16,17,18,19		; 	 		; 
				
		ORG	$B600		; Save code in EPROM
		LDAA 	#00
		STAA 	holdI
**** START OF MAIN PROGRAM ****
Main 		LDS	#$01FF 		; Initialize SP
		LDX 	#MSG1 		; Load X with base address of MSG1
		JSR 	OUTSTRG 
		JSR	OUTCRLF		; Call subroutine to print MSG1
*Prepares for the Print function
		LDX	#Matrix		;Loads X with Matrix 0,0
		PSHX			;Pushes X for holding
		BSR 	PRINTMAT 	;Call subroutine to print original matrix
		PULX			;Pulls X back out
*Prepares and does the swap matrix function		
		LDAA	#N		;Load A with N 
		LSRA			;Divides N by 2
		LDAB	#M		;Loads M in B
		LDY	#Matrix + (M*(N-1))	;Loads Y with the position of the swap row
		PSHX			;Pushes X to store #matrix again
		BSR 	SWAPMAT 	;Call subroutine to swap matrix columns
		PULX			;Pulls X
*Prepares for the new print function
		LDX 	#MSG2		;Load X with base address of MSG2
		JSR 	OUTSTRG 	;Call subroutine to print MSG2
		JSR	OUTCRLF		;Prints a new line
		LDAA	#00		;Loads A with 0
		STAA	holdI		;Loads holdI with 0 again
		LDX	#Matrix		;Reloads X with Matrix
		BSR	PRINTMAT 	;Call subroutine to print modified matrix
		SWI 			; return to Buffalo monitor

**** CODE FOR SUBROUTINES GOES HERE ****
PRINTMAT 	LDAB	#00		;Loads B with 0 (will be a counter)
rowPrint	LDAA	holdI		;HoldI is a counter for A(Subrotiune messes w/ A)
		CMPA	#N		;Compare holdI with N
		BEQ	donePrint	;Done printing if they are equal
colPrint	CMPB	#M		;Compare B with M
		BEQ	nextRow		;If equal then it is done with that row
		INCB			;Increament B if not
		JSR	OUT1BTY		;Print X and inc X
		BRA	colPrint	;Repeat till row is done.
nextRow		JSR	OUTCRLF		;Make a new line feed
		LDAB	#00		;Reload B with 0 to start a new row
		INC	holdI		;Increament holdI counter
		BRA	rowPrint	;Repeat till all rows are complete
donePrint	RTS			; Return from subroutine

*Swap Matrix function is below
SWAPMAT		PSHA		;Push A and B to store for counters
		PSHB		;.
		LDAA	0,X	;Swap X and Y (EG 0,0 and 3,0)
		LDAB	0,Y	;.
		STAA	0,Y	;.
		STAB	0,X	;.
		INX		;Move up X and Y
		INY		;.
		PULB		;Pull back A and B 
		PULA		;.
		DECB		;Dec B (the amount of columns)
		TSTB		;Test if it's 0
		BNE	SWAPMAT	;Otherwise repeat till 0
		LDAB	#M	;Reload M into B for next row
		PSHA		;Push A and B
		PSHB		;.
		XGDY		;Switch Y to D for operations
		SUBD	#M*2	;Set D to 2*row values higher (next row)
		XGDY		;Switch D back to Y(X is inc to proper spot)
		PULB		;Pull A and B
		PULA		;.
		DECA		;Dec A for row amount
		TSTA		;Test A for 0
		BNE	SWAPMAT	;Otherwise loop again
doneSwap	RTS 		;Return from subroutine

**** DEFINE MESSAGES ****
MSG1		FCC 	"The original matrix is as follows:"
		FCB	$04
MSG2		FCC 	"The modified matrix is as follows:"
		FCB	$04