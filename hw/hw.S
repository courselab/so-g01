#    SPDX-FileCopyrightText: 2001 Monaco F. J. <monaco@usp.br>
#    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
#    SPDX-FileCopyrightText: 2024 Lucas Zanotti <lucas.zanotti@usp.br>
#   
#    SPDX-License-Identifier: GPL-3.0-or-later
#
#  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
#  and contains modifications carried out by the following author(s):
#  Lucas Zanotti <lucas.zanotti@usp.br>

.code16
.global _start
_start:
	movb $0xe, %ah
	movw $0x0, %si
loop:			      
	movb msg(%si), %al
	cmp $0x0, %al
	je halt
	int $0x10
	add $0x1, %si
	jmp loop
halt:
	hlt
	jmp halt
msg:
	.string "Hello World"
	.fill 510 - (. - _start), 1, 0
	.word 0xaa55
