*Darrell Percey  DATE: 4/16/17
*Lab 8
*Program: Runs a signal out of OC2 pin based on the
*values of the PORTC pins 2-0. The lookup tables 
*HIGH_VAL and LOW_VAL give the values for each of 
*the different setting portC can have.

REGBAS		EQU		$1000
PORTA		EQU		$00
PORTC		EQU		$03
DDRC		EQU		$07
*Timer Values
TOC2		EQU		$18
TCNT		EQU		$0E
TCTL1		EQU		$20
TFLG1		EQU		$23
TOGGLE		EQU		$40
OC2		EQU		$40
CLEAR		EQU		$40

		ORG		$00
HIGH_VAL	FDB		200,600,400,500,600,350,400,450		;High values 
LOW_VAL		FDB		1800,1400,600,500,400,150,100,50	;Low values

		ORG		$B600
		LDX		#REGBAS			
		Bclr		DDRC,X,%11111111		;Set Input/Output for PORTC
		BSET		PORTA,X,OC2				;Set PORTA (OC2 ping)
		LDAA		#TOGGLE					;Toggle the OC2
		STAA		TCTL1,X					;"
		LDAB		PORTC,X	
		ANDB 		#$07				;Find value of PORTC
		LDY		#HIGH_VAL				;"
		LSLB
		ABY							;"
		LDD		Tcnt,X					;Load D with the running timer
		ADDD		0,Y					;Add D with the first value of high/C
		STD		TOC2,X					;"
		LDAA		#CLEAR					;Clear the flag
		STAA		TFLG1,X	
*HIGH_SET changes to a low value of the PORTC value
HIGH_SET	BRCLR		TFLG1,X,OC2		HIGH_SET	;Loop until flag set				;Catch the time of the OC2 ping
		LDAB		PORTC,X					;Find the value of PORTC
		ANDB		#$07
		LDY		#LOW_VAL
		LSLB							;Lookup table for low values
		ABY							;Find PORTC+Low value table
		LDD		TOC2,X
		ADDD		0,Y					;Add cycles to current time
		STD		TOC2,X					;Store value in the OC2 timer
		LDAA		#CLEAR					;Clear the flag
		STAA		TFLG1,X					
*LOW_SET changes to a high value of the PORTC value
LOW_SET		BRCLR		TFLG1,X OC2		LOW_SET		;Steps are similar for HIGH_SET	
		LDAA		#CLEAR
		STAA		TFLG1,X
		LDAB		PORTC,X
		ANDB		#$07
		LDY		#HIGH_VAL
		LSLB
		ABY		
		LDD		TOC2,X
		ADDD		0,Y
		STD		TOC2,X
		BRA		HIGH_SET
		SWI
