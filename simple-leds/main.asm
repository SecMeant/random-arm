; Main function cut from binary file
; Program sets two leds on and exits
; Using GPIOE and HAL calls
; THIS FILE IS NOT GENERATED BY GCC IT IS MODIFIED BY HOOOOMAN
; who knows what I could mess up, so watch out ;]

main:
.LFB126:
	.loc 1 73 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI7:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 81 0
	bl	HAL_Init
.LVL11:
	.loc 1 88 0
	bl	SystemClock_Config
.LVL12:
	.loc 1 95 0
	bl	MX_GPIO_Init
.LVL13:
	.loc 1 103 0
	mov r4, #0x48 ; Prepare for moving 0x48001000
	mov r1, #12   ; which is GPIOE constant
	asr r4, r1    ; r4 = 48000
	add r4, #1    ; r4 = 48001
	asr r4, r1    ; r4 = 48001000
	mov	r1, #256  ; PIN id
	bl	HAL_GPIO_TogglePin
.LVL14:
	.loc 1 104 0
	; r4 has already GPIOE contant in it
	mov	r1, #512
	bl	HAL_GPIO_TogglePin
.LVL15:
	.loc 1 107 0
	movs	r0, #0
	pop	{r4, pc}
.L18:
	.align	2
.L17:
	.word	1207963648
	.cfi_endproc
