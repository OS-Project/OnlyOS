OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */


C_STACK_SIZE = 0x100000; /* 1M */
SVC_STACK_SIZE = 0x100000;
IRQ_STACK_SIZE = 1024;


MEMORY
{
    SDRAM (rwx) : ORIGIN = 0x80000000, LENGTH = 512M;
    CODE (rx) : ORIGIN = 0x80000000, LENGTH = 1M;
    HEAP (rw) : ORIGIN = 0x80100000, LEGNTH = 1M;
    STACK (rw) : ORIGIN = 0x80200000, LEGNTH = 1M;
}

SECTIONS
{
    . = 0x80000000;
    .text :
    {
        _stext = .;
        *(.text.interrupt_vector_table)
        *(.text.boot)
        _etext = .;
    } > CODE

    .rodata :
    {
        _srodata = .;
        *(.rodata)
        _erodata = .;
    } > CODE

    .data :
    {
        _sdata = .;
        *(.data)
        _edata = .;
    } > CODE

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } > CODE

    .heap :
    {
        _sheap = .;
        . = . + 0x6400000; /* 100 Mo */
        _eheap = .;
    } > HEAP

    .stack :
    {
        _sstack = .;
        _s_irq_stack = .;
        . += IRQ_STACK_SIZE;
        _e_irq_stack = .;

        _s_svc_stack = .;
        . += SVC_STACK_SIZE;
        _e_svc_stack = .;

        _s_c_stack = .;
        . += C_STACK_SIZE;
        _e_c_stack = .;

        _estack = .;
    } > STACK

    /* C lib */
    heap_low = _sheap;
    heap_top = _eheap;
}
