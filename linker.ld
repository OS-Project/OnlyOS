OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */
/*
MEMORY
{
    ROM : ORIGIN = 0x80000000, LENGTH = 50M
    RAM : ORIGIN = (0x80000000 + 50M), LENGTH = 112M
    HEAP : ORIGIN = 0x80000000 + 50M + 112M, LENGTH = 250M
    STACK : ORIGIN = 0x9FFFFFFF, LENGTH = 100M

}
*/
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
	}

	.rodata :
	{
	    __rodata_start = .;
        *(.rodata)
        __rodata_end = .;
	}

	.data :
	{
	    __data_start = .;
		*(.data)
        __data_end = .;
	}

	.bss :
	{
	    __bss_start = .;
		bss = .;
		*(.bss)
		__bss_end = .;
	}
}
