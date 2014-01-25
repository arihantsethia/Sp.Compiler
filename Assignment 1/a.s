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
movq	$6,%rbx
cmp	%rbx, %rax
jge .L0
movq	$6,%rcx
movq	%rcx,-8(%rbp)
.L0:
movq	-8(%rbp), %rcx
pushq	%rcx
movq	$6,%rcx
movq	-8(%rbp), %rdx
addq	%rdx,%rcx
pushq	%rcx
popq	%rcx
popq	%rcx
popq	%rcx
leave
ret
