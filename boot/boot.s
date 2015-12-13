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

    // Set up the stack: last available ram address: 0xBFFF_FFFF (datasheet p179), minus 512MB.
    stack_init:
        mov	sp, #0xA0000000

	bss_init:
        ldr	r0, =_sbss
        ldr	r1, =_ebss
        cmp r0,r1

        beq call_main
        mov	r4, #0

        write_zero:
                strb r4, [r0]
                add r0,r0,#1
                cmp	r0, r1
                bne	write_zero

    call_main:
        b	main

halt:
	b	halt
