section	.text
	global	ft_isspace

ft_isspace:
	mov		rax, 9

.loop:
	cmp		al, 12
	jg		.check_space
	cmp		dil, al
	je		.is
	inc		al
	jmp		.loop

.check_space:
	cmp dil, 32
	je	.is
	xor	eax, eax
	ret

.is:
	mov rax, 1
	ret
