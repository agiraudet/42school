section	.text
	global	ft_list_size

ft_list_size:
	xor		eax, eax

.loop:
	test	rdi, rdi
	je		.exit
	mov		rdi, [rdi + 8]
	inc		rax
	jmp		.loop

.exit:
	ret
