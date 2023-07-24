section	.text
	global	ft_read
	extern	__errno_location

ft_read:
	mov		rax, 0
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
