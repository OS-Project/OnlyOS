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
        _stext = .;
		*(.text.exception_vectors)
		*(.text.boot)
		_etext = .;
	} > ROM

	.rodata :
	{
        _srodata = .;
        *(.rodata)
        _erodata = .;
	} > ROM

	.data :
	{
        _sdata = .;
		*(.data)
		_edata = .;
	} > ROM

	.bss :
	{
        _sbss = .;
		*(.bss)
		_ebss = .;
	} > ROM
}