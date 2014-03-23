.LC0: 
	.string	"%lld\n" 
	.text 
	.globl	main
	.type	main, @function 
main: 
.LFB0: 
pushq	%rbp
movq	%rsp, %rbp
movq	$5,%rax
movq	$10,%rbx
movq	$11,%rcx
movq	$10,%rdx
movq	$12,%r8
imulq	%r8,%rdx
subq	%rdx,%rcx
movq	$13,%rdx
movq	$15,%r8
movq	$7,%r9
movq	$10,%r10
movq	$11,%r11
movq	$2,%r12
addq	%r12,%r11
movq	$8,%r12
movq	$7,%r13
movq	$3,%r14
pushq	%r14
movq	$9,%r14
popq	%r15
subq	%r14,%r15
pushq	%r15
movq	$2,%r15
popq	%r14
addq	%r15,%r14
imulq	%r14,%r13
addq	%r13,%r12
movq	$5,%r13
subq	%r13,%r12
movq	$7,%r13
movq	$8,%r14
pushq	%r14
movq	$3,%r14
pushq	%r14
movq	$4,%r14
popq	%r15
imulq	%r14,%r15
pushq	%r15
movq	$5,%r15
pushq	%r15
movq	$9,%r15
pushq	%r15
movq	$10,%r15
pushq	%r15
movq	$3,%r15
pushq	%r15
movq	$7,%r15
pushq	%r15
movq	$9,%r15
pushq	%r15
movq	$10,%r15
pushq	%r15
movq	$20,%r15
pushq	%r15
movq	$2,%r15
pushq	%r15
movq	$1,%r15
pushq	%r15
movq	$5,%r15
pushq	%r15
movq	$3,%r15
popq	%r14
addq	%r15,%r14
popq	%r15
imulq	%r14,%r15
popq	%r14
addq	%r15,%r14
popq	%r15
pushq	%rax
pushq	%rdx
movq	%r15, %rax
movq	%rax, %rdx
sarq	$63, %rdx
idivq	%r14
movq	%rax, %r15 
popq	%rdx
popq	%rax
popq	%r14
addq	%r15,%r14
popq	%r15
imulq	%r14,%r15
popq	%r14
addq	%r15,%r14
popq	%r15
imulq	%r14,%r15
popq	%r14
subq	%r15,%r14
popq	%r15
imulq	%r14,%r15
popq	%r14
addq	%r15,%r14
popq	%r15
pushq	%rax
pushq	%rdx
movq	%r15, %rax
movq	%rax, %rdx
sarq	$63, %rdx
idivq	%r14
movq	%rax, %r15 
popq	%rdx
popq	%rax
popq	%r14
addq	%r15,%r14
imulq	%r14,%r13
addq	%r13,%r12
subq	%r12,%r11
imulq	%r11,%r10
subq	%r10,%r9
imulq	%r9,%r8
addq	%r8,%rdx
subq	%rdx,%rcx
imulq	%rcx,%rbx
addq	%rbx,%rax
pushq	%rax
movq	%rax, %rsi
movq	$.LC0, %rax
movq	%rax, %rdi
movq	$0, %rax
call	printf
.L0:
movq	-8(%rbp), %rax
movq	$100,%rbx
cmpq	%rbx, %rax
jg .L1
movq	$1,%rcx
pushq	%rcx
.L2:
movq	-16(%rbp), %rcx
movq	$50,%rdx
cmpq	%rdx, %rcx
jg .L3
movq	-8(%rbp), %r8
movq	$101,%r9
cmpq	%r9, %r8
jl .L4
movq	$5000,%r10
movq	%r10,-8(%rbp)
.L4:
movq	-16(%rbp), %r10
movq	$1,%r11
addq	%r11,%r10
movq	%r10,-16(%rbp)
jmp	.L2
.L3:
movq	-8(%rbp), %r10
movq	$1,%r11
addq	%r11,%r10
movq	%r10,-8(%rbp)
popq	%r10
jmp	.L0
.L1:
movq	-8(%rbp), %r10
movq	$1000,%r11
imulq	%r11,%r10
movq	$5000,%r11
addq	%r11,%r10
pushq	%r10
.L5:
movq	-16(%rbp), %r10
movq	$10,%r11
pushq	%rax
pushq	%rdx
movq	%r10, %rax
movq	%rax, %rdx
sarq	$63, %rdx
idivq	%r11
movq	%rax, %r10 
popq	%rdx
popq	%rax
movq	-8(%rbp), %r11
cmpq	%r11, %r10
jl .L6
movq	-16(%rbp), %r12
movq	$10,%r13
pushq	%rax
pushq	%rdx
movq	%r12, %rax
movq	%rax, %rdx
sarq	$63, %rdx
idivq	%r13
movq	%rax, %r12 
popq	%rdx
popq	%rax
movq	%r12,-16(%rbp)
jmp	.L5
.L6:
movq	-16(%rbp), %r12
movq	-8(%rbp), %r13
subq	%r13,%r12
movq	%r12,-16(%rbp)
movq	-16(%rbp), %r12
movq	%r12,-8(%rbp)
popq	%r12
movq	-8(%rbp), %r12
pushq	%r12
popq	%r12
popq	%r12

leave
ret
