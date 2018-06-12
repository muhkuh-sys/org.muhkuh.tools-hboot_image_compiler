
MEMORY
{
	ASSERT_EMPTY(rwx)  : ORIGIN = 0x00000000, LENGTH = 0
	CODE(rx)           : ORIGIN = 0x04000000, LENGTH = 0x00000100
	DATA0(rx)          : ORIGIN = 0x04000100, LENGTH = 0x00000100
	DATA1(rx)          : ORIGIN = 0x04000200, LENGTH = 0x00000100
	DATA2(rx)          : ORIGIN = 0x04000300, LENGTH = 0x00000100
	DATA3(rx)          : ORIGIN = 0x04000400, LENGTH = 0x00000100
}


/* Section Definitions */
SECTIONS
{
	.assert_empty (NOLOAD) :
	{
		/* NOTE: include all sections here which should be empty.
		 */
		*(.data)
		*(.glue*)
		*(.vfp11_veneer)
		*(.v4_bx)
	} >ASSERT_EMPTY


	.code ORIGIN(CODE) :
	{
		KEEP(*(.init_code))
		*(.text .rodata .rodata*)
	} >CODE

	.data0 ORIGIN(DATA0) :
	{
		KEEP(*(.a))
	} >DATA0

	.data1 ORIGIN(DATA1) :
	{
		KEEP(*(.b))
	} >DATA1

	.data2 ORIGIN(DATA2) :
	{
		KEEP(*(.c))
	} >DATA2

	.data3 ORIGIN(DATA3) :
	{
		KEEP(*(.d))
	} >DATA3

	.bss :
	{
		PROVIDE ( __bss_start__ = . );
		*(.bss COMMON)
		PROVIDE ( __bss_end__ = . );
	} >CODE

	.stack :
	{
		/* Reserve the rest of the section for the stack. */
		. = ORIGIN(CODE) + LENGTH(CODE);
		PROVIDE ( stack_top = . );
	} >CODE

	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
	Symbols in the DWARF debugging sections are relative to the beginning
	of the section so we begin them at 0.  */
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
}

