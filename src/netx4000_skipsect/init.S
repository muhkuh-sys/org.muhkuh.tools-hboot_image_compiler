	.section .init_code, "ax"

	.global start

@--------------------------------------

	.arm


    .func start, start
    .type start, STT_FUNC
start:
	b       start
    .endfunc

@--------------------------------------


	.section .a, "a"

	.long 0x11111111


@--------------------------------------


	.section .b, "a"

	.long 0x22222222


@--------------------------------------


	.section .c, "a"

	.long 0x33333333


@--------------------------------------


	.section .d, "a"

	.long 0x44444444


  .end

