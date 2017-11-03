	;Lab_7 Parallel I/O Ports and Intefacing
	;20170405

	; Port variables
regbas	EQU  $1000	; I/O register block base address
portb	EQU  $04		; offset of portb data register from regbas (portb is the 7 segment display)
portc	EQU  $03		; offset of portc data register from regbas
ddrc	EQU  $07		; offset of ddrc register from regbas

	; 7-segment variables (not sure the order the 
	; light is decoded in. dp, a, b, ...g or g, f, e...dp)?
	ORG  $00
zero	FCB  $0A	;?
one	FCB  $EB
two	FCB  $46
three	FCB  $62
four	FCB  $A3
five	FCB  $32
six	FCB  $12
seven	FCB  $6B
eight	FCB  $02
nine	FCB  $23
clear	FCB  $FF	;? no lights on
astriek	FCB  $07
hashtag	FCB  $F7
a	FCB  $03
b	FCB  $00
c	FCB  $1E
d	FCB  $08

	; Scan-key variables
	ORG  $100
colcntr	RMB  1
row	RMB  1
col	RMB  1
key	RMB  1
r_list 	FCB  $EB,$46,$62,$03	;keypad lay out based off of hex code
	FCB  $A3,$32,$12,$00
	FCB  $6B,$02,$23,$1E
	FCB  $07,$0A,$F7,$08	;needs the hex for zero

	; Main routine	
main	ORG  $B600
	LDS  #$1FF	;init stack pointer

	JSR  disp_data	;program requirement 1

loop1	JSR  scan_key	;program requirement 2
	JSR  which_key		
	JSR  display
	BRA  loop1
	SWI

	;Subroutine will load the values for 0-9 and send them to 
	;portb. The values 0-9 will show up on the 
	;seven-segment-display twice and then gets cleared.
disp_data
	LDAB #0		;init loop3 (outer loop) counter
loop3	LDAA #0		;init loop2 (inner loop) counter
	LDY  #zero	;load first number to be displayed into register y
loop2	JSR  display	;run subroutine to display what is in register y
	JSR  delay	;run subroutine to delay for 1/3 a second
	INY 		;load register y with next number
	INCA		;increment the loop2 counter
	CMPA #17		
	BNE  loop2	;have we displayed all numbers?
	INCB		;increment the loop3 counter
	CMPB #2	
	BNE  loop3	;have we displayed the numbers twice?
	LDY #clear
	BSR display	;clears out the display
	RTS

	;Subroutine displays the content stored in 
	;memory location 0,Y on portb 
display	PSHA
	PSHX 
	LDX  #regbas	; base address of I/O register block
	LDAA  0,Y		; loads register a with value to be displayed
	STAA  portb,X	; sends data in register a to portb (7 segment display)
	PULX		; restores register x and a with previous values
	PULA
	RTS

	;Subroutine scans keypad continously until a button is pushed. The 
	;row and coloumn is then used to identify which button was pressed.
scan_key	LDX  #regbas	; base address of I/O register block
		LDAA 	#$F0		
		STAA 	ddrc,X		
reset		LDAB	#$00
		STAB 	colcntr
		STAB	row
		STAB	col
oneLoop		BSET	portc,X,%11100000
		BCLR	portc,X,%00010000
		BRA	row_col
twoLoop		INC	col
		BSET	portc,X,%11010000
		BCLR	portc,X,%00100000
		BRA	row_col
threeLoop	INC	col
		BSET 	portc,X,%10110000
		BCLR	portc,X,%01000000
		BRA	row_col
fourLoop	INC	col
		BSET	portc,X,%01110000
		BCLR	portc,X,%10000000
		BRA	row_col
row_col 	BRCLR	portc,X,%00000001,	exit
		INC	row
		BRCLR	portc,X,%00000010, 	exit
		INC	row
		BRCLR	portc,X,%00000100,	exit
		INC	row
		BRCLR	portc,X,%00001000,	exit
		LDAB 	#$00
		STAB	row
		LDAB	col
		CMPB	#$00
		BEQ	twoLoop
		CMPB	#$01
		BEQ	threeLoop
		CMPB	#$02
		BEQ	fourLoop
		CMPB	#$03
		BEQ	reset
exit		RTS		; a key is pressed.


	; Subroutine will determine which key was
	;pressed and will store the look
	;up table value in Y.
which_key 
	LDAA row		
	LDAB #4		; four elements per row
	MUL		; offset away from list base
	ADDB col		
	LDY  #r_list	
	ABY		; register y equals the offset from the list base

	; Subroutine delays for 1/3 a second 
delay	PSHX
	LDX  #$D902	
loop4	NOP
	NOP
	NOP
	DEX
	BNE  loop4 
	PULX
	RTS