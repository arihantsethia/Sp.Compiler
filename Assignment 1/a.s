.LC0: 
	.string	"%d\n" 
	.text 
	.globl	main
	.type	main, @function 
main: 
.LFB0: 
pushq	%rbp
movq	%rsp, %rbp
movq	$5,%rax
pushq	%rax
.L0:
movq	-8(%rbp), %rax
movq	$0,%rbx
cmp	%rbx, %rax
jl .L1
movq	$.LC0, %rax
movq	-8(%rbp), %rsi
movq	%rax, %rdi
movq	$0, %rax
call	printf
movq	-8(%rbp), %rcx
movq	$1,%rdx
subq	%rdx,%rcx
movq	%rcx,-8(%rbp)


jmp	.L0
.L1:
movq	$6,%rcx
movq	-8(%rbp), %rdx
addq	%rdx,%rcx
pushq	%rcx
popq	%rcx
popq	%rcx
leave
ret
