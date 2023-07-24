section	.text
	global	ft_list_delone
	extern	free

ft_list_delone:
	push	rdi
	mov		rdi, [rdi]
	call	rsi
	pop		rdi
	call	free
	ret
