section	.text
	global	ft_strcpy

ft_strcpy:
	xor		ecx, ecx

.cpy:
	movzx	rdx, byte [rsi + rcx]
	mov		[rdi + rcx], dl
	test	dl, dl
	je		.exit
	inc		rcx
	jmp		.cpy

.exit:
	mov		rax, rdi
	ret
