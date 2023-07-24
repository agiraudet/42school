section .text
	global	ft_checkbase
	extern	ft_isspace
	extern	ft_getindex

ft_checkbase:
	push	rsi
	push	rbx
	push	rcx
	push	rdx
	xor		eax, eax
	mov		rcx, rdi
	mov		rsi, rdi

.loop:
	movzx	rdi, byte[rcx]
	cmp		dil, 0
	je		.good_base
	call	ft_isspace
	cmp		rax, 1
	je		.bad_base
	cmp		dil, 45
	je		.bad_base
	cmp		dil, 43
	je		.bad_base
	jmp		.ck_double_init

.bad_base:
	xor		eax, eax
	jmp		.exit

.good_base:
	mov		rax, 1
	jmp		.exit

.ck_double_init:
	mov		rdx, -1
	xor		rbx, rbx

.ck_double:
	inc		rdx
	cmp		byte[rsi + rdx], 0
	je		.ck_double_exit
	cmp		dil, byte[rsi +rdx]
	jne		.ck_double
	inc		rbx
	jmp		.ck_double

.ck_double_exit:
	inc		rcx
	cmp		rbx, 1
	jg		.bad_base
	jmp		.loop

.exit:
	pop		rdx
	pop		rcx
	pop		rbx
	pop		rsi
	ret
