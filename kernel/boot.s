.global _start
.global _sstack                  
.global _sbss
.global _ebss
.global start_boot

.equ  UND_STACK_SIZE, 0x8
.equ  ABT_STACK_SIZE, 0x8
.equ  FIQ_STACK_SIZE, 0x8
.equ  IRQ_STACK_SIZE, 0x100
.equ  SVC_STACK_SIZE, 0x8

.equ  MODE_UND, 0x1B     
.equ  MODE_USR, 0x10            
.equ  MODE_FIQ, 0x11
.equ  MODE_IRQ, 0x12
.equ  MODE_SVC, 0x13
.equ  MODE_ABT, 0x17
.equ  MODE_SYS, 0x1F            

.equ  I_bit, 0xC0               

.text
.code 32
.global _start
.global error

.include "kernel/interrupt.s"

.section ".text.boot"
_start:
	// Disable irqs and fiqs first
	stack_init:
		ldr r0, =_estack
        	msr cpsr_c, #MODE_UND | I_bit
       		mov sp, r0
		sub r0, r0, #UND_STACK_SIZE

		msr cpsr_c, #MODE_SVC | I_bit
        	mov sp, r0
		sub r0, r0, #SVC_STACK_SIZE

        	msr cpsr_c, #MODE_ABT | I_bit
        	mov sp, r0
		sub r0, r0, #ABT_STACK_SIZE

        	msr cpsr_c, #MODE_IRQ | I_bit
        	mov sp, r0
		sub r0, r0, #IRQ_STACK_SIZE

        	msr cpsr_c, #MODE_FIQ | I_bit
        	mov sp, r0
		sub r0, r0, #FIQ_STACK_SIZE

        	// Kernel mode
        	msr cpsr_c, #MODE_SYS | I_bit
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
            cmp	r0, r1
            bne	write_zero

	call_main:
		ldr pc,=kmain
		
	// If kmain returns, exit with error

error:
	mov r0, #1
	b kexit

.end
    
