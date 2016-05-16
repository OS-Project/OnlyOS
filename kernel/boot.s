.text
.section ".text.boot"
.global _start
.global error
.arm	// Arm mode

_start:
    .equ    sys_mode, 0b11111         // System mode
    .equ    und_mode, 0b11011         // Undefined mode
    .equ    abort_mode, 0b10111       // Abort mode
    .equ    svc_mode, 0b10011         // Supervisor mode
    .equ    irq_mode, 0b10010         // Interrupt mode
    .equ    fiq_mode, 0b10001         // Fast interrupt

    stack_init:
        msr cpsr, #svc_mode
        ldr r0, =_e_svc_stack
        mov sp, r0

        msr cpsr, #irq_mode
        ldr r0, =_e_irq_stack
        mov sp, r0


        // Kernel mode
        msr cpsr, #sys_mode
        ldr r0, =_e_sys_stack
        mov sp, r0

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

    // Arguments not defined
    call_main:
        b	kmain


error:
	mov r0, #1
	b kexit

halt:
	// TODO: Remove interrupts
	mov r0, #0 // No error
    b	kexit
