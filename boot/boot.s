.section ".text.interrupt_vector_table"
interrupt_vector_table:
    b _start // Reset Handler
    b . // Undefined instruction
    b swi_handler // SWI Handler (Software interrupt)
    b . // Prefetch Abort
    b . // Data Abort
    b . // Reserved
    b irq_handler // IRQ
    b . // FIQ


.section ".text.boot"
.global _start
.arm	// Arm mode

_start:

    .equ    sys_mode, 0b11111         // System mode
    .equ    und_mode, 0b11011         // Undefined mode
    .equ    abort_mode, 0b10111       // Abort mode
    .equ    svc_mode, 0b10011         // Supervisor mode
    .equ    irq_mode, 0b10010         // Interrupt mode
    .equ    fiq_mode, 0b10001         // Fast interrupt

    stack_init:
        //msr cpsr, #svc_mode
        ldr r0, =_e_svc_stack
        mov	sp, r0

        msr cpsr, #irq_mode
        ldr r0, =_e_svc_stack
        mov sp, r0


        //msr cpsr, #und_mode
        //msr cpsr, #abort_mode
        //msr cpsr, #fiq_mode
        msr cpsr, #sys_mode

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
        b	kmain

halt:
    b	halt
