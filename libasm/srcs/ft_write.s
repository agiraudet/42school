section	.text
	global	ft_write
	extern	__errno_location

ft_write:
	mov		rax, 1
	syscall
	cmp		rax, 0
	jge		.exit
	mov		rcx, rax
	call	__errno_location
	neg		rcx
	mov		[rax], rcx
	mov		rax, -1
	ret

.exit:
	ret
