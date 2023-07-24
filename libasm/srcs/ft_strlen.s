;size_t		ft_strlen(const char *s);
;rax		ft_strlen(rdi);

section .text
	global ft_strlen

ft_strlen:
	xor	rax,rax

.count:
	cmp	byte [rdi + rax], 0
	je	.exit
	inc	rax
	jmp	.count

.exit:
	ret
