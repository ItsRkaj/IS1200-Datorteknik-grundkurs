  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2016-2017.
  # Last modified 2018-03-04 by Oliver Wilén & Filip Hedlund
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.text
.globl	hexasc
.globl	atof
.globl	delay
.globl	loop1
.globl	loop2
.globl	loopend
.globl	time2string

  # You can add your own code here
  #

  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

hexasc:	andi	$v0,$a0,0xF
	addi	$v0,$v0,0x30
	nop

	ble	$v0,0x39,atof
	nop

	addi	$v0,$v0,7
atof:
	jr	$ra
	nop

delay:
	li	$t0,0
loop1:
	li	$t1,0
	li	$t2,4711
	beq	$t0,3000,loopend
	nop
	addi	$t0,$t0,1
	j	loop2
	nop
loop2:
	beq	$t1,$t2,loop1
	nop
	addi	$t1,$t1,1

	j	loop2
	nop

loopend:
	jr 	$ra
	nop

time2string:
	PUSH	$s0
	PUSH	$s1
	PUSH	$s2
	PUSH	$s3
	PUSH	$s4
	PUSH	$s5
	PUSH	$s6
	PUSH	$s7


	PUSH	$ra
	move	$t5,$a0
	PUSH	$t5
	move	$a0,$a1

	jal	hexasc
	nop
	move	$s0,$v0

	srl	$a0,$a0,4
	jal	hexasc
	nop
	move	$s1,$v0

	srl	$a0,$a0,4
	jal	hexasc
	nop
	move	$s2,$v0

	srl	$a0,$a0,4
	jal	hexasc
	nop
	move	$s3,$v0

	li	$s4,0x3a
	li	$s5,0x00

	POP	$t5
	move	$a0,$t5

	sb	$s3,0($a0)
	sb	$s2,1($a0)
	sb	$s4,2($a0)
	sb	$s1,3($a0)
	beq	$s0,0x39,nine
	nop
	sb	$s0,4($a0)
	sb	$s5,5($a0)

	POP	$ra

	POP	$s7
	POP	$s6
	POP	$s5
	POP	$s4
	POP	$s3
	POP	$s2
	POP	$s1
	POP	$s0

	jr	$ra
	nop

	nine:

	li	$s0,0x4e
	li	$s6,0x49
	li	$s7,0x45

	sb	$s0,4($a0)
	sb	$s6,5($a0)
	sb	$s0,6($a0)
	sb	$s7,7($a0)
	sb	$s5,8($a0)

	POP	$ra

	POP	$s7
	POP	$s6
	POP	$s5
	POP	$s4
	POP	$s3
	POP	$s2
	POP	$s1
	POP	$s0

	jr	$ra
	nop
