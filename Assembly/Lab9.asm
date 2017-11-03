REGBAS		EQU	$1000
TCFLG1		EQU	$23	; input capture flag 
TCT12		EQU	$21	; input capture edge set
CLEAR		EQU	$04	; clear for flag
IC1RISE		EQU	$10	; set to rising edges
TIC1		EQU	$10	; IC1 timer
TMSK1		EQU	$22	; register for IC1 interrupts 
IC1FM		EQU	$FB
IC1I		EQU	$04

OUTA		EQU	$FFB8 	; Address of OUTA Buffalo subroutine
OUTSTRG 	EQU	$FFC7 	; Address of OUTSTRG Buffalo subroutine
OUTLHLF 	EQU	$FFB2 	; Address of OUTLHLF Buffalo subroutine
OUTRHLF 	EQU	$FFB5 	; Address of OUTRHLF Buffalo subroutine
OUTCRLF 	EQU	$FFC4 	; Address of OUTCRLF Buffalo subroutine

SEC_OUTER	EQU	10
SEC_INNER	EQU	18181		; .01seconds in e clock cycles
LOW_FREQ	EQU	20000		; e clock cycles for 100Hz
HI_FREQ		EQU	200		; e clock cycles for 10kHz

		ORG	$00
edge		RMB	2
tempEdge	RMB	2
period		RMB	2
freq		RMB	2
temp		RMB	2
freqH		RMB	2
buffer		RMB	5

		ORG	$E8
		JMP	IC1_ISR


********************Start of Main Program **********************
		ORG	$B600
		LDS	#$01FF
		LDX	#REGBAS
		CLR	edge
		BSR	IC1_INIT	; Call subroutine INIT
MAIN_LOOP	CLI			; Enable global interrupts
		LDAA	#SEC_OUTER	; Loads A with 10 for mul
OUTER_SEC	LDY	#SEC_INNER	; Loads Y with 18181
INNER_SEC	NOP			; 2 clock cycles
		NOP			; 2 clock cycles
		DEY			; 4 clock cycles
		BNE	INNER_SEC	; check if inner is 0
		DECA			; if 0 start outer
		BNE	OUTER_SEC	; 18181*11*10 = 199910 + 40+20+30 = 2000000 = 1 second
		SEI			; Disable interrupts
		LDD	period		; loads the period
		CPD	#LOW_FREQ	; Compares to low frequnecy
		BHS	LOW_MESSAGE	; Display low message
		CPD	#HI_FREQ	; Compares to high frequnecy
		BLS	HIGH_MESSAGE	; Display high message
		BRA	DISP_MESSAGE	; Display frequency
****************Displays low message then repeats********************
LOW_MESSAGE	LDX	#LOWMSG
		JSR	OUTSTRG 
		JSR	OUTCRLF
		CLR	period	
		BRA	MAIN_LOOP
****************Displays high message then repeats*******************
HIGH_MESSAGE	LDX	#HIGHMSG
		JSR	OUTSTRG 
		JSR	OUTCRLF
		CLR	period	
		BRA	MAIN_LOOP
*************Displays frequency message then repeats*****************
DISP_MESSAGE	LDX	period
		LDD	#32		; Load D with 32
		FDIV			; D/X -> X: R->D
		STX	temp		; Store X in temp
		LDD	temp		; Load temp to D
		LSRD			; Divide
		LSRD			;
		LSRD			;
		CLR	freqH		; Clear FreqH
		STAA	freqH+1		; Store upper byte in freqH+1
		LSRD			; Divide
		LSRD			;
		STD	temp		; 
		XGDX
		SUBD	temp
		XGDX
		LSRD
		STD	temp
		ADDA	freqH+1
		STAA	freqH+1
		XGDX
		SUBD	temp
		ADDD	freqH
		STD	freqH
		BSR	CONVERT_DEC	; Converts Hex to Decimal
		LDX	#DISPLAY	; Displays message before freqency
		JSR	OUTSTRG		; 
		BSR	DISPLAY_DEC	; Displays the decimal
		JSR	OUTCRLF
		JMP	MAIN_LOOP

IC1_INIT	LDAA	#IC1RISE
		STAA	TCT12,X
		BSET	TMSK1,X,IC1I
		LDAA	#CLEAR
		STAA	TCFLG1,X
		RTS

CONVERT_DEC	PSHX
		PSHB
		PSHA
		LDX	#10000		; Load 10000 to X
		IDIV			; D/X -> X: R->D
		XGDX			
		ADDB	#$30		; Convert to ASCII
		STAB	buffer		; Store buffer
		XGDX
		LDX	#1000		; Load 1000 to X
		IDIV			; D/X -> X: R->D
		XGDX
		ADDB	#$30		; Convert to ASCII
		STAB	buffer+1	; Store buffer
		XGDX
		LDX	#100		; Load 100 to X
		IDIV			; D/X -> X: R->D
		XGDX	
		ADDB	#$30		; Convert to ASCII
		STAB	buffer+2	; Store buffer
		XGDX
		LDX	#10		; Load 10 to X
		IDIV			; D/X -> X: R->D
		ADDB	#$30		; Convert to ASCII
		STAB	buffer+4	; Store buffer
		XGDX
		ADDB	#$30		; Convert to ASCII
		STAB	buffer+3	; Store buffer
		PULA
		PULB
		PULX
		RTS

PRINT_SPACE	PSHA
		INX			; increament X
		LDAA	#$20		; Load A with Space
		JSR	OUTA		; Print space
		PULA			; Pull out value
		RTS


DISPLAY_DEC	LDX	#buffer
		LDAA	#$30
		CMPA	0,X
		BNE	TEN_K
		BSR	PRINT_SPACE
		CMPA	0,X
		BNE	ONE_K
		BSR	PRINT_SPACE
		BSR	PRINT_SPACE
		DEX
		CMPA	0,X
		BNE	ONE_H
		BSR	PRINT_SPACE
		CMPA	0,X
		BNE	TENS
		BSR	PRINT_SPACE
		BRA	ONES
TEN_K		LDAA	0,X
		JSR	OUTA
		INX
ONE_K		LDAA	0,X
		JSR	OUTA
		LDAA	#$2C
		JSR	OUTA
		INX
ONE_H		LDAA	0,X
		JSR	OUTA
		INX
TENS		LDAA	0,X
		JSR	OUTA
		INX
ONES		LDAA	0,X
		JSR	OUTA
		RTS
		

IC1_ISR		LDX	#REGBAS
		LDD	TIC1,X		; Load the time in TIC1
		STD	tempEdge	; Store it in tempEdge
		LDY	#edge		; Load previous edge
		SUBD	0,Y		; Subtract
		STD	period		; Save the period
		LDD	tempEdge	; Switch tempEdge to edge
		STD	edge		; 
		LDAA	#CLEAR		; Clear the flag
		STAA	TCFLG1,X
		RTI
		
************************* Display Messages *************************

LOWMSG		FCC	"The signal's frequency is lower than 100Hz"
		FCB	$04

HIGHMSG		FCC	"The signal's frequency is greater than 10kHz"
		FCB	$04			
		
DISPLAY		FCC	"The signal's frequency is "
		FCB	$04	
		SWI
