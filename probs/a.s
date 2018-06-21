	.file	"test-opti-rm-unused-var.cpp"
	.text
	.section	.text._ZN2IOD2Ev,"axG",@progbits,_ZN2IOD5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN2IOD2Ev
	.type	_ZN2IOD2Ev, @function
_ZN2IOD2Ev:
.LFB8313:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA8313
	movq	2000016(%rdi), %rdx
	leaq	1000000(%rdi), %rax
	movl	$1, %esi
	movq	stdout(%rip), %rcx
	movq	%rax, %rdi
	subq	%rax, %rdx
	jmp	fwrite@PLT
	.cfi_endproc
.LFE8313:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN2IOD2Ev,"aG",@progbits,_ZN2IOD5Ev,comdat
.LLSDA8313:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE8313-.LLSDACSB8313
.LLSDACSB8313:
.LLSDACSE8313:
	.section	.text._ZN2IOD2Ev,"axG",@progbits,_ZN2IOD5Ev,comdat
	.size	_ZN2IOD2Ev, .-_ZN2IOD2Ev
	.weak	_ZN2IOD1Ev
	.set	_ZN2IOD1Ev,_ZN2IOD2Ev
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB8323:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$1, %esi
	leaq	_ZSt4cerr(%rip), %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE8323:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_io, @function
_GLOBAL__sub_I_io:
.LFB9629:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	call	__cxa_atexit@PLT
	leaq	1000000+io(%rip), %rax
	leaq	__dso_handle(%rip), %rdx
	movq	%rax, 2000016+io(%rip)
	leaq	-1000000(%rax), %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	leaq	_ZN2IOD1Ev(%rip), %rdi
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE9629:
	.size	_GLOBAL__sub_I_io, .-_GLOBAL__sub_I_io
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_io
	.globl	io
	.bss
	.align 32
	.type	io, @object
	.size	io, 2000032
io:
	.zero	2000032
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 8.1.1 20180531"
	.section	.note.GNU-stack,"",@progbits
