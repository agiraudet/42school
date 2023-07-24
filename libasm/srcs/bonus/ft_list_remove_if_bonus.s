section	.text
	global	ft_list_remove_if
	extern	free

ft_list_remove_if:
	mov		r15, rsi
	mov		r14, rdx
	mov		r13, rcx
	mov		r12, rdi
	mov		rdi, [rdi]
	mov		rbx, [rdi + 8]
	xor		ecx, ecx
	call	.cmpr
	test	al, al
	je		.delfirst
	mov		rcx, rdi

.current:
	test	rdi, rdi
	je		.exit
	push	rcx
	push	rbx
	call	.cmpr
	pop		rbx
	pop		rcx
	test	al, al
	je		.delone

.nextelem:
	mov		rcx, rdi
	mov		rdi, rbx
	test	rdi, rdi
	je		.exit
	mov		rbx, [rdi + 8]
	jmp		.current

.cmpr:
	push	rdi
	mov		rdi, [rdi]
	mov		rsi, r15
	call	r14
	pop		rdi
	ret

.delone:
	push	rbx
	push	rcx
	push	rdi
	mov		rdi, [rdi]
	call	r13
	pop		rdi
	call	free
	pop		rcx
	pop		rbx
	test	rbx, rbx
	je		.exit_last
	mov		rdi, rbx
	mov		rbx, [rdi + 8]
	mov		[rcx + 8], rdi
	jmp		.current

.delfirst:
	mov		rcx, [r12]
	mov		[r12], rbx
	jmp		.delone

.exit:
	ret

.exit_last:
	xor	r8d, r8d
	mov	[rcx + 8], r8
	ret
