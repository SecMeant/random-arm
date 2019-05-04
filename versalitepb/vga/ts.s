.text
.global start
.extern main

start:
	ldr sp, =stack_top
	bl main
	b .
