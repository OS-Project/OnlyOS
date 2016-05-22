#ifndef ONLYOS_INTERRUPT_H
#define ONLYOS_INTERRUPT_H
	void INT_SVC_handler();
	void INT_SVC_call(int r0, int r1, int r2, int r3));
	extern svc_asm_call(int r0, int r1, int r2, int r3);
#endif
