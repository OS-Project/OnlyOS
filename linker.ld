OUTPUT_ARCH(arm)
ENTRY(_start)	/* Entry point of the program */

MEMORY
{
    ROM : ORIGIN = 0x80000000, LENGTH = 0x10000
}

SECTIONS
{
	/* Start address depends on u-boot */
	. = 0x80000000;
	.text :
	{
        __text_start = .;
		*(.text.idt)
		*(.text.boot)
		__text_end = .;
	} > ROM


	/*
	__rodata_start = .;
	.rodata :
	{
        	*(.rodata)
	}
	__rodata_end = .;


	__data_start = .;
	.data :
	{
		*(.data)
	}

	__data_end = .;


	__bss_start = .;
	.bss :
	{
		bss = .;
		*(.bss)
	}
	__bss_end = .;
    */
}
