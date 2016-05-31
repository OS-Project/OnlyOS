.text
.code 32

.include "kernel/boot/boot_header.h"
.include "kernel/interrupt/interrupt.s"

.section ".text.boot"
_start:	
	stack_init:
		// Stack is empty descending.
		ldr r0, =_estack
        	msr cpsr_c, #MODE_UND | IRQ_BIT | FIQ_BIT
       		mov sp, r0
		sub r0, r0, #UND_STACK_SIZE

		msr cpsr_c, #MODE_SVC | IRQ_BIT | FIQ_BIT
        	mov sp, r0
		sub r0, r0, #SVC_STACK_SIZE

        	msr cpsr_c, #MODE_ABT | IRQ_BIT | FIQ_BIT
        	mov sp, r0
		sub r0, r0, #ABT_STACK_SIZE

        	msr cpsr_c, #MODE_IRQ | IRQ_BIT | FIQ_BIT
        	mov sp, r0
		sub r0, r0, #IRQ_STACK_SIZE

        	msr cpsr_c, #MODE_FIQ | IRQ_BIT | FIQ_BIT
        	mov sp, r0
		sub r0, r0, #FIQ_STACK_SIZE

        	// Kernel mode
        	msr cpsr_c, #MODE_SYS | IRQ_BIT | FIQ_BIT
        	mov sp, r0    
                 
	bss_init:
        	ldr	r0, =_sbss
        	ldr	r1, =_ebss
        	cmp r0,r1

        	beq call_main
        	mov	r4, #0

		write_zero:
        		strb r4, [r0]
        		add r0, r0,#1
        		cmp r0, r1
			bne write_zero

	// Disable fiq. Enable irq
	//cpsie i
	//cpsid f

	call_main:
		ldr pc,=kmain
		
	// If kmain returns, exit with error

error:
	cpsid i
	mov r0, #1
	b kexit

.global set_vectorBaseAddr 
set_vectorBaseAddr:
	MCR     p15, #0, r0, c12, c0, #0
	DSB
	BX      lr
.end
    
