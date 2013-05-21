	.file	"ContextSwitch.c"
	.section	.rodata
.LC0:
	.string	"main"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$20, %esp
	movl	$4000, (%esp)
	call	malloc
	movl	%eax, -8(%ebp)
	addl	$16000, -8(%ebp)
	movl	$.LC0, (%esp)
	call	puts
	movl	-8(%ebp), %eax
#APP
	pushl %ebp;movl %esp, %eax;movl %eax, %esp;movl %esp, %ebp;pushl %ebp;subl $4, %esp;call foo;leave;movl %eax, %esp;leave;
#NO_APP
	movl	%eax, -12(%ebp)
	movl	$.LC0, (%esp)
	call	puts
	addl	$20, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.section	.rodata
.LC1:
	.string	"foo"
	.text
.globl foo
	.type	foo, @function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$.LC1, (%esp)
	call	puts
	leave
	ret
	.size	foo, .-foo
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-48)"
	.section	.note.GNU-stack,"",@progbits
