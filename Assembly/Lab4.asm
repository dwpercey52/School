*Name: Darrell Percey   Date:2/21/2017
*Program: Checks an array for and stores the 
*amount of even/odd/positive/negative numbers into
*the reserved memory location for each of these.

*Declaring all varibles needed.
		ORG		$00
N		EQU		10
EVEN		RMB		1
ODD		RMB		1
NEG		RMB		1
POS		RMB		1
*Sets the array values 
		ORG		$0100
ARR		FCB		$72,$60,$48,$2A,$06,$54,$21,$83,$F5,$97

		ORG		$B600
*Clears all variables to ensure 0 for each.
		LDAA		#$00	;Loads register A with 0
		STAA		EVEN	;Makes even 0
		STAA		ODD	;Makes odd 0
		STAA		NEG	;Makes neg 0
		STAA		POS	;Makes pos 0
*Start of the loop/Checks for even/odd
		LDX		#ARR	;Loads X with position of ARR[0]
loop		BRCLR		0,X $01 	evenLoop	;checks if LSB is clear
		LDAA		ODD	;Loads A with odds value
		INCA			;Increments that value
		STAA		ODD	;Stores the value back
		BRA		nextCheck	;Branches to pos/neg check
*Adds if even below and branches above if odd added
evenLoop	LDAA		EVEN	;Loads A with even
		INCA			;Increments that value
		STAA		EVEN	;Stores the value back
*Checks for a positive/negative number.
nextCheck	BRCLR		0,X $80		posLoop		;checks if MSB is clear
		LDAA		NEG	;Loads A with neg
		INCA			;Increments that value
		STAA		NEG	;Stores that value back
		BRA		lastCheck	;Branches to array value check
*Branches to the last check if negative and adds if positive
posLoop		LDAA		POS	;Loads a with pos
		INCA			;Increments that value
		STAA		POS	;Stores the value back
*Checks the current position of the array if it's the last number
lastCheck	CPX		#ARR+N-1	;Compares X to ARR+(N-1) position
		BEQ		end	;If compare is equal then end program
		INX			;Else increament X position by one
		BRA		loop	;Back to top of the loop
end		SWI
	
	