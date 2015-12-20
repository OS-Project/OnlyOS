OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

MEMORY
{
    ROM : ORIGIN = 0x80000000, LENGTH = 50M
}
/* End of RAM is 0xBFFF_FFFF - 512M */

SECTIONS
{
	/* Star from the begining of the RAM */
	. = 0x80000000;
	.text :
	{
        __text_start = .;
		*(.text.exception_vectors)
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
	} > ROM

	.bss :
	{
	    __bss_start = .;
		bss = .;
		*(.bss)
		__bss_end = .;
	} > ROM
}
