OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

MEMORY
{
    ROM : ORIGIN = 0x80000000, LENGTH = 50M
    RAM : ORIGIN = ORIGIN(ROM) + LENGTH(ROM), LENGTH = 112M
    HEAP : ORIGIN = ORIGIN(RAM) + LENGTH(RAM), LENGTH = 250M
    STACK : ORIGIN = , LENGTH = 100M
}

SECTIONS
{
	/* Star from the begining of the RAM */
	. = 0x80000000;
	.text :
	{
        __text_start = .;
		*(.text.idt)
		*(.text.boot)
		__text_end = .;
	} > ROM

	.rodata :
	{
	    __rodata_start = .;
        *(.rodata)
        __rodata_end = .;
	} > ROM

	.data :
	{
	    __data_start = .;
		*(.data)
        __data_end = .;
	} > RAM

	.bss :
	{
	    __bss_start = .;
		bss = .;
		*(.bss)
		__bss_end = .;
	} > RAM

	__heap_start = ORIGIN(HEAP);
	__heap_end = ORIGIN(HEAP) + LENGTH(HEAP) - 1;
}
