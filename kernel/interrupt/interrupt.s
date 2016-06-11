.section ".text.vector_table"
.global vector_table
vector_table:
	b _start
	ldr pc,=error // Undefined instruction
	ldr pc,=svc_handler
	ldr pc,=error // Prefetch abort
	ldr pc,=error // Data abort
	nop
	ldr pc,=irq_handler
	ldr pc,=error // FIQ

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

	// Restore context. Return argument is in r0.
	ldmfd sp!, {r1}
	msr spsr, r1
	ldmfd sp!, {r4-r12,lr}
	mov r1, lr
	msr cpsr, r1
        movs pc,lr

svc_asm_call:	
	svc #0
	mov pc, lr
