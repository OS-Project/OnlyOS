OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

SYS_STACK_SIZE = 0x100000; /* 1M */
C_STACK_SIZE = 0x100000; /* 1M */
SVC_STACK_SIZE = 0x100000; /* 1M */
IRQ_STACK_SIZE = 1024;

MEMORY
{
    CODE (rwx) : ORIGIN = 0x80000000, LENGTH = 50M
    HEAP (rwx) : ORIGIN = 0x83200000, LENGTH = 100M
    STACK (rwx) : ORIGIN = 0x89600000, LENGTH = 50M
}

SECTIONS
{
    . = 0x80000000;
    .text :
    {
        _stext = .;
	*(.text.boot) 
	*(.text.interrupt_handler)
        
	*(.text)
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
        _eheap = .;
    } > HEAP

    .stack :
    {
        _sstack = .;
        _estack = .;
    } > STACK
}
