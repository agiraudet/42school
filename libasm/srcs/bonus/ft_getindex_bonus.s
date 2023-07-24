section	.text
	global	ft_getindex

ft_getindex:
	mov		rax, -1
	xor		ecx, ecx

.count:
	cmp		byte[rsi + rcx], 0
	je		.exit
	cmp		dil, byte[rsi + rcx]
	je		.exit_ok
	inc		rcx
	jmp		.count

.exit:
	ret

.exit_ok:
	mov		rax, rcx
	ret
