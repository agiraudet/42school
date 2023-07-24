section	.text
	global ft_strcmp

ft_strcmp:
	movzx	ecx, byte[rsi]
	movzx	eax, byte[rdi]
	test	cl, cl
	je		.exit
	cmp		cl, al
	jne		.exit
	inc		rsi
	inc		rdi
	jmp		ft_strcmp

.exit:
	sub		eax, ecx
	ret
