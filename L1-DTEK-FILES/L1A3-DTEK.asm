# labwork.S
# Written 2015-2017 by F Lundevall
# Skeleton file for IS1200/IS1500 lab 1.
# The macros PUSH and POP are in the public domain.
# Please add your own code at the end of the file.

#
# Please keep the two macros PUSH and POP unchanged
#
.macro    PUSH reg
  addi    $sp,$sp,-4
  sw    \reg,0($sp)
.endm

.macro    POP reg
  lw    \reg,0($sp)
  addi    $sp,$sp,4
.endm
#
# Please add your own code below this line
#
.data
.align 2
mytime:    .word 0x5957
timstr:    .ascii "text more text lots of text\0"
.text
main:
# print timstr
la    $a0,timstr
li    $v0,4
syscall
nop
# wait a little
li    $a0,2
jal    delay
nop
# call tick
la    $a0,mytime
jal    tick
nop
# call your function time2string
la    $a0,timstr
la    $t0,mytime
lw    $a1,0($t0)
jal    time2string
nop
# print a newline
li    $a0,10
li    $v0,11
syscall
nop
# go back and do it all again
j    main
nop
# tick: update time pointed to by $a0
tick:    lw    $t0,0($a0)    # get time
addiu    $t0,$t0,1    # increase
andi    $t1,$t0,0xf    # check lowest digit
sltiu    $t2,$t1,0xa    # if digit < a, okay
bnez    $t2,tiend
nop
addiu    $t0,$t0,0x6    # adjust lowest digit
andi    $t1,$t0,0xf0    # check next digit
sltiu    $t2,$t1,0x60    # if digit < 6, okay
bnez    $t2,tiend
nop
addiu    $t0,$t0,0xa0    # adjust digit
andi    $t1,$t0,0xf00    # check minute digit
sltiu    $t2,$t1,0xa00    # if digit < a, okay
bnez    $t2,tiend
nop
addiu    $t0,$t0,0x600    # adjust digit
andi    $t1,$t0,0xf000    # check last digit
sltiu    $t2,$t1,0x6000    # if digit < 6, okay
bnez    $t2,tiend
nop
addiu    $t0,$t0,0xa000    # adjust last digit
tiend:    sw    $t0,0($a0)    # save updated result
jr    $ra        # return
nop

.globl time2string
time2string:
PUSH     $ra
PUSH     $s0
PUSH     $s1

addi     $s0, $a0, 0
addi     $s1, $a1, 0

#first number xx:x=
srl     $a0, $s1, 12  # shift for the right number
andi     $a0, $a0, 0xf # have to mask it to make it show the right value
jal     hexasc
nop
sb     $v0, 0($s0)

#second number x=:xx
srl     $a0, $s1, 8  # shift for the right number
andi     $a0, $a0, 0xf #masking
jal     hexasc
nop
sb     $v0, 1($s0)

#the comma :
addi     $t0, $0, 0x3a
sb     $t0, 2($s0)

#third number xx:=x
srl     $a0, $s1, 4 #  shift for the right number
andi     $a0, $a0, 0xf # masking
jal     hexasc
nop
sb     $v0, 3($s0)

#fourth number =x:xx
srl     $a0, $s1, 0  # shift for the right number
andi     $a0, $a0, 0xf # masking
jal     hexasc
nop
sb     $v0, 4($s0)

#null
addi     $t0, $0, 0x00
sb     $t0, 5($s0)


POP     $s1
POP     $s0
POP     $ra

# you can write your code for subroutine "hexasc" below this line
#
hexasc:
ble     $a0, 15, letter
nop
andi     $a0, $a0, 0x0f

letter:    ble     $a0, 9, less10
nop
addi     $a0, $a0, 55
move     $v0, $a0
jr     $ra
nop

less10:    addi     $a0, $a0, 48
nop
move     $v0, $a0
jr     $ra
nop

.globl delay
delay:
whileloop:
beqz    $a0,whileloopdone    # while statement(ms > 0)
nop
addi     $a0, $a0, -1     # ms--
li      $t0,0        # i = 0

forloop:
beq     $t0, 4700, forloopdone # for statement is (i == x)
nop
addi     $t0, $t0, 1 # i++
j     forloop


forloopdone:
j     whileloop
nop

whileloopdone:
jr     $ra
nop
