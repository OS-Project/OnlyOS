#ifndef ONLYOS_INTERRUPT_H
#define ONLYOS_INTERRUPT_H
	void INT_SVC_handler(int r0, int r1, int r2, int r3);
	void INT_SVC_call(int r0, int r1, int r2, int r3);
	extern void svc_asm_call(int r0, int r1, int r2, int r3);
#endif
