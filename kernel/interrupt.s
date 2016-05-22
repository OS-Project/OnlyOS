.section ".text.interrupt_handler"
.global svc_asm_call

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

svc_asm_call:
	stmfd sp!, {lr}
	svc #0
	ldmfd sp!, {pc}
