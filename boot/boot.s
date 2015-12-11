.section ".text.idt"
idt:
	b _start // Reset Handler
	b . // Undefined instruction
	b . // SWI Handler (Software interrupt)
	b . // Prefetch Abort
	b . // Data Abort
	b . // Reserved
	b . // IRQ
	b . // FIQ

.section ".text.boot"

.global _start
.arm	// Arm mode
_start:

	// Set up the stack: last available ram address (grows downward): 0xBFFF_FFFF (datasheet p179) so 0xC000_0000 (first push is downward)
	mov	sp, #0xA0000000
	/*
	// Clear .bss
        ldr	r0, =__bss_start
        ldr	r1, =__bss_end
        mov	r4, #0

	zero:
        	strb	r4, [r0], #1 // Write zero and increment _bss_start address
        	cmp	r0, r1
        	bne	zero
	*/

	b	main

	// If returns from C, loop here forever
halt:
	b	halt
