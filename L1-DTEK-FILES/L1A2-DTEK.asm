	.text
main: 
	li	$a0,15
	
	jal	hexasc
	nop
	
	move	$a0,$v0
	
	li	$v0,11
	syscall
	
stop:	j	stop
	nop


hexasc:
	li	$t3,9
	li	$t1,0xf
	and	$v0,$a0,$t1
	ble	$v0,$t3,less
	addi	$v0,$v0,0x37
	jr 	$ra
	nop

less:
	addi	$v0,$v0,0x30
	jr	$ra
	nop
	