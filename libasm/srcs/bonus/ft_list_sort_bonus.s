section	.text
	global	ft_list_sort

ft_list_sort:
	mov		r12, rdi		;original pointer
	xor		r14d, r14d
	mov		r13, rsi		;&ft_cmp
	mov		rdi, [rdi]		;current elem

.loop:
	mov		rsi, [rdi + 8]
	test	rsi, rsi
	je		.exit
	call	.cmpr
	cmp		al, 0
	jg		.swap
	mov		r14, rdi
	mov		rdi, rsi
	jmp		.loop

.cmpr:
	push	rsi
	push	rdi
	mov		rsi, [rsi]
	mov		rdi, [rdi]
	xor		eax, eax
	call	r13
	pop		rdi
	pop		rsi
	ret

.swap:
	xor		edx, edx

	mov		rdx, [rsi + 8]	;2nd in rdx
	mov		[rsi + 8], rdi	;prev->next = 2nd elem
	mov		[rdi + 8], rdx	;1st->next = next elem

	test	r14, r14
	jne		.setprev
	je		.setpoint

.setprev:
	mov		[r14 + 8], rsi
	mov		rdi, [r12]
	xor		r14d, r14d
	jmp		.loop

.setpoint:
	mov		[r12], rsi
	mov		rdi, rsi
	jmp		.loop

.exit:
	ret
