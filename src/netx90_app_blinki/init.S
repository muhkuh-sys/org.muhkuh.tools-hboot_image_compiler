	.section .init_code, "ax"

	.extern blinki_main
	.extern stack_top

	.global start

#include "asic_types.h"

@--------------------------------------

@ The Cortex-M4 in the netX90 is a THUMB-only CPU.
@ All others start in 32 bit mode.
#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90_MPW_APP || ASIC_TYP==ASIC_TYP_NETX90 || ASIC_TYP==ASIC_TYP_NETX90_APP
	.syntax unified
	.thumb
#else
	.arm
#endif


    .func start, start
    .type start, STT_FUNC
start:
    @ b start
	@ Set own stack position.
	ldr     r2, =stack_top
	mov     sp, r2

#if ASIC_TYP==ASIC_TYP_NETX10
	@ copy the data section
	ldr     r2, =__data_loadaddr__
	ldr     r3, =__data_start__
	ldr     r4, =__data_end__
copy_data:
	cmp     r3, r4
	ldrlo   r5, [r2], #4
	strlo   r5, [r3], #4
	blo     copy_data
#endif

	@ Clear the .bss section (zero init).
	mov     r2, #0
	ldr     r3, =__bss_start__
	ldr     r4, =__bss_end__
clear_bss:
	str     r2, [r3], #4
	cmp     r3, r4
	bmi     clear_bss

	b       blinki_main
    .endfunc

@--------------------------------------

  .end

