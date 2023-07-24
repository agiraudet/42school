section	.text
	global	ft_atoi_base
	extern	ft_getindex
	extern	ft_strlen
	extern	ft_isspace
	extern	ft_checkbase

ft_atoi_base:
	push	rdi
	mov		rdi, rsi			;set strlen param
	call	ft_strlen
	mov		rbx, rax			;store base_len in rbx
	cmp		rbx, 1
	jle		.base_error
	call	ft_checkbase
	test	rax, rax
	je		.base_error
	pop		rdi
	mov		rcx, rdi			;store str_to_decrypt in rcx
	xor		eax, eax			;same as mov rax, 0

.space:
	movzx	rdi, byte[rcx]		;move the next char to rdi
	call	ft_isspace
	cmp		rax, 1
	jne		.sign_init
	inc		rcx
	jmp		.space

.sign_init:
	mov		rax, 1

.sign:
	movzx	rdi, byte[rcx]
	cmp		dil, 45
	je		.sign_neg
	cmp		dil, 43
	je		.sign_pos
	push	rax

.atoi_init:
	xor		eax, eax

.count:
	movzx	rdi, byte[rcx]		;move the next char to rdi

	cmp		dil , 0				;check for end of str
	je		.exit

	push	rax
	push	rcx
	call	ft_getindex			;get index of current char in base_str
	mov		rdx, rax
	pop		rcx
	pop		rax
	cmp		rdx, -1				;if char not in base_str
	je		.exit

	imul	rax, rbx
	add		rax, rdx			;result = result * base_len + char_index

	inc		rcx					;loop to next char of str_to_decrypt
	jmp		.count

.exit:
	pop		rcx
	imul	rax, rcx
	ret

.sign_neg:
	imul	rax, -1
	inc		rcx
	jmp		.sign

.sign_pos:
	inc		rcx
	jmp		.sign

.base_error:
	pop		rdi
	xor		eax, eax
	ret
