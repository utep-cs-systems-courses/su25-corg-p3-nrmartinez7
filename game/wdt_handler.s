;;handlers interrupts, 
	.text
	.balign 2
	.section __interrupt_vector_11, "ax"
	.word WDT
	.text

	.extern wdt_c_handler
	.extern redrawScreen

WDT:
	push r15		;save registers
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push r7
	push r6
	push r5
	push r4

	call #wdt_c_handler	;call to handler timer for mole

	pop r4			;restore registers
	pop r5
	pop r6
	pop r7
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

	cmp #0, &redrawScreen	;check if screen needs to be redrawn
	jz dont_wake		
	and #0xFFEF, 0(r1)	;cpu wakes up after interrupt

dont_wake:
	reti			;return from interrupt
	
