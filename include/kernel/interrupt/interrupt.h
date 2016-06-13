#ifndef ONLYOS_INTERRUPT_H
#define ONLYOS_INTERRUPT_H
	void INT_SVC_handler(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3);
	void INT_SVC_call(int r0, int r1, int r2, int r3);
	void INT_IRQ_handler();
	extern void svc_asm_call(int r0, int r1, int r2, int r3);
#endif
