	.file	"simdgcc.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB2558:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movabsq	$4611686019492741120, %rax
	movq	%rax, -24(%rbp)
	movabsq	$4657622734849703936, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %xmm1
	movq	-16(%rbp), %xmm0
	movq	%xmm0, %xmm0
	movq	%xmm1, %xmm1
	addps	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	nop
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2558:
	.size	main, .-main
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
