.section ".text.vector_table"
vector_table:
	ldr pc,=_start
	b error // Undefined instruction
	b svc_handler
	b error // Prefetch abort
	b error // Data abort
	nop
	b irq_handler
	b error // FIQ

.section ".text.interrupt_handler"
.global svc_handler
.global svc_asm_call
.global irq_handler

irq_handler:
        // Done auto: spsr = cpsr. Ref: p456
        stmfd sp!, {r0-r12,lr} // Save registers
        mrs r11, spsr // Save context

        // r0 contains the interrupt id
        ldr r0, =0x48200040 // Ref: p183 (Interrupt controller), p470
        and r0, r0, #0b1111111 // Ref: p475

        // Branch table
	ldr pc,=INT_IRQ_handler

        // Interrupt has been taken care of. Enable new interrupts
        mov r0, #0x1
        ldr r1, =0x48200048 // Ref: p457
        str r0, [r1]
        dsb // Data synchronization barrier. Ref: p458

        msr cpsr, r11 // Restore context
        ldmfd sp!, {r0-r12, lr} // Restore the saved registers from the stack
        subs pc, lr, #4
        // Done auto: cpsr = spsr; pc=lr. Ref: p458

svc_handler:
	// Save context
	stmfd sp!, {r4-r12,lr}
	mrs r4, spsr
	stmfd sp!, {r4}

	// Call the handler
	bl INT_SVC_handler

	// Restore context
	ldmfd sp!, {r0}
	msr spsr, r0
	ldmfd sp!, {r4-r12,lr}
	mov r0, lr
	msr cpsr, r0
        movs pc,lr

svc_asm_call:	
	svc #0
	mov pc, lr