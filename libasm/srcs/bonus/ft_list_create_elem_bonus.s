section	.text
	global	ft_create_elem
	extern	malloc

ft_create_elem:
	push	rdi
	mov		rdi, 16
	call	malloc
	pop		rdi
	mov		rcx, 0
	mov		[rax], rdi
	mov		[rax + 8], rcx
	ret
