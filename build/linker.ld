OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

MEMORY
{
    RAM : ORIGIN = 0x80200000, LENGTH = 300M
}

SECTIONS
{
    /* Start address depends on u-boot */
    . = 0x80200000;
    .text :
    {
        _stext = .;
        *(.text.interrupt_vector_table)
        *(.text.boot)
        _etext = .;
    } > RAM

    .rodata :
    {
        _srodata = .;
        *(.rodata)
        _erodata = .;
    } > RAM

    .data :
    {
        _sdata = .;
        *(.data)
        _edata = .;
    } > RAM

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } > RAM

    /* HEAP memory */
    heap_low = .;
    . = . + 0x6400000; /* 100 Mo d'espace HEAP */
    heap_top = .;
}
