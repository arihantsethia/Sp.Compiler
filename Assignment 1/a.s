.LC0: 
	.string	"%d" 
	.text 
	.globl	main
	.type	main, @function 
main: 
.LFB0: 
pushq	%rbp
movq	%rsp, %rbp
movq	$5,%rax
pushq	%rax
movq	-8(%rbp), %rax
pushq	%rax
movq	$6,%rax
movq	-8(%rbp), %rbx
addq	%rbx,%rax
pushq	%rax
popq	%rax
popq	%rax
popq	%rax
leave
ret
