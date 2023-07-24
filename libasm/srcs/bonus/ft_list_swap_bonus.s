section	.text
	global	ft_list_swap

ft_list_swap:
	mov		rsi, [rdi + 8]
	mov		rdx, [rsi + 8]
	mov		rcx, [rdx + 8]
	mov		[rdi + 8], rdx
	mov		[rsi + 8], rcx
	mov		[rdx + 8], rsi
	ret
