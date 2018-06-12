	.section .init_code, "ax"

@--------------------------------------

	.arm


    .func start, start
    .type start, STT_FUNC
start:
	b       start
    .endfunc

@--------------------------------------

  .end

