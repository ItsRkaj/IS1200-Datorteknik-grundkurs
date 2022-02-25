main:	li 	$a0, 1000 	#a0 = 1000 ms = 1 sec
	addi 	$a0,$a0, -1 	#Becouse they need to be the same in our delay loop and the while loop said ms > 0 we have to subtract 1 from ms
	jal 	delay		#Jump to delay function
	nop
	j 	stop

delay:	j 	loop
	li 	$t0, 0
	bne 	$a0,$0,delay
	nop
	addi 	$a0, $a0, -1
	jr 	$ra

loop: 	li 	$t1, 67000
	bne 	$t0,$t1, loop
	addi 	$t0, $t0, 1
	j 	delay
	nop

stop: 	j 	stop
	nop
