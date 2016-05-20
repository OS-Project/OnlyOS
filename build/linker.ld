OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

SYS_STACK_SIZE = 0x100000; /* 1M */
C_STACK_SIZE = 0x100000; /* 1M */
SVC_STACK_SIZE = 0x100000; /* 1M */
IRQ_STACK_SIZE = 1024;

MEMORY
{
    CODE (rw) : ORIGIN = 0x80000000, LENGTH = 50M
    HEAP (rw) : ORIGIN = 0x83200000, LENGTH = 100M
    STACK (rw) : ORIGIN = 0x89600000, LENGTH = 50M
}

SECTIONS
{
    . = 0x80000000;
    .text :
    {
        _stext = .;
        *(.text.interrupt_vector_table)
	*(.text.interrupt_handler)
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
        _theap = .;
    } > HEAP

    .stack :
    {
        _sstack = .;

        _s_sys_stack = .;
        . += SYS_STACK_SIZE;
        _e_sys_stack = .;

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
}
