.section ".text.interrupt_vector_table"
interrupt_vector_table:
	b _start // Reset Handler
	b error // Undefined instruction
	b svc_handler // SVC Handler (Software interrupt)
	b error // Prefetch Abort
	b error // Data Abort
    	b error // Reserved
	b error // IRQ
	b error // FIQ

.section ".text.interrupt_handler"
fiq_handler:
        // Done auto: spsr = cpsr. Ref: p456
        stmfd sp!, {r0-r12,lr} // Save registers
        mrs r11, spsr // Save context

        // r0 contains the interrupt id
        ldr r0, =0x48200044 // Ref: p183 (Interrupt controller), p470
        and r0, r0, #0b1111111 // Ref: p476

        // Branch table

        // Interrupt has been taken care of. Enable new interrupts
        mov r0, #0x2
        ldr r1, =0x48200048 // Ref: p457
        str r0, [r1]
        dsb // Data synchronization barrier. Ref: p458

        msr cpsr, r11 // Restore context
        ldmfd sp!, {r0-r12, lr} // Restore the saved registers from the stack
        subs pc, lr, #4
        //Done auto: cpsr = spsr; pc=lr. Ref: p458

irq_handler:
        // Done auto: spsr = cpsr. Ref: p456
        stmfd sp!, {r0-r12,lr} // Save registers
        mrs r11, spsr // Save context

        // r0 contains the interrupt id
        ldr r0, =0x48200040 // Ref: p183 (Interrupt controller), p470
        and r0, r0, #0b1111111 // Ref: p475

        // Branch table

        // Interrupt has been taken care of. Enable new interrupts
        mov r0, #0x1
        ldr r1, =0x48200048 // Ref: p457
        str r0, [r1]
        dsb // Data synchronization barrier. Ref: p458

        msr cpsr, r11 // Restore context
        ldmfd sp!, {r0-r12, lr} // Restore the saved registers from the stack
        subs pc, lr, #4
        //Done auto: cpsr = spsr; pc=lr. Ref: p458

svc_handler:
        mrs r11, cpsr

        msr cpsr, r11
        movs pc,lr



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
        msr cpsr, #svc_mode
        ldr r0, =_e_svc_stack
        mov	sp, r0

        //msr cpsr, #irq_mode
        //ldr r0, =_e_irq_stack
        //mov sp, r0


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
