section	.text
	global	ft_list_push_front
	extern	ft_create_elem

ft_list_push_front:
	push	rdi
	mov		rdi, rsi
	call	ft_create_elem
	pop		rcx
	mov		rdi, [rcx]
	mov		[rax + 8], rdi 
	mov		[rcx], rax
