.LC0: 
	.string	"%d" 
	.text 
	.globl	main
	.type	main, @function 
main: 
.LFB0: 
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq $5,%rax
	movq %rax,-4(%rbp)
	movq -4(%rbp), %rax
	movq %rax,-8(%rbp)
		movq $6,%rax
		pushq %rax
		movq -4(%rbp), %rax
		popq %rbx
		add %rbx,%rax
		movq %rbx,-12(%rbp)
	leave
	ret
