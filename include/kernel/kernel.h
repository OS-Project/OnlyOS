//
// Created by Thibault PIANA on 10/11/15.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_KERNEL_H
#define ONLYOS_KERNEL_H
    typedef struct  {
        // Compilation informations
        char* _COMPILATION_TIME;
        char* _COMPILATION_DATE;

        char SYSTEM_DMTIMER;
        char SYSTEM_WDT;
        // Bus UART for std
        char SYSTEM_STDOUT;
        char SYSTEM_STDERR;
        char SYSTEM_STDIN;
    } SYSTEM;

    int kmain();
    int kinit();
extern void set_vectorBaseAddr(unsigned int addr);
	extern void svc_handler();
    void kinit_vector_table();
    void kexit(int errnum);
#endif //ONLYOS_KERNEL_H

#ifdef __cplusplus
}
#endif
