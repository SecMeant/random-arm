ENTRY(start)
SECTIONS
{
	. = 0x10000;
	.text : { ts.o *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss)  }
	.datt : { *(image.o) }
	. =ALIGN(8);
	. = . + 0x1000;
	stack_top = .;
}
