.data
	promptMessage: .asciiz "Enter Array Size: "
	promptMessage2: .asciiz "Enter Integer: "
	resultMessage: .asciiz "Sorted Array: "
	space: .asciiz " "
	arraySize: .word 0
.text
	main:
		add $t0, $zero, $zero # Register for both array size and array address
		add $t1, $zero, $zero # Register for both loop2's counter and array elements
		addi $t2, $zero, 4 # Register for both moving array address and array elements
		add $t3, $zero, $zero # Register for both outterLoop's counter and initializing array address
		
		li $v0, 4
		la $a0, promptMessage # Prompt the user to set array size.
		syscall
		
		li $v0, 5 # Get array size from the user.
		syscall
		
		sw $v0, arraySize # Store user input into arraySize.
		lw $a0, arraySize # Get array size from arraySize.
		move $s0, $a0 # Move array size to $s0.
		
		jal makingArray	# Call makingArray function.
		jal bubbleSort # Call bubbleSort function.
		jal printArrayElements # Call printArrayElements function.
		
		li $v0, 10 # Finish the program.
		syscall
		
	makingArray:
		
		mul $t0, $s0, 4 # $t0 = ArraySize * 4 -> size of memory
		
		li $v0, 9 # Syscall 9 -> Allocating memory.
		move $a0, $t0 
		syscall
		
		move $v1, $v0 # Base address of array
		li $s1, 0 # loop's counter value
	loop:
		beq $s1, $s0, exit # Case: $s1 = $s0 go to exit.
		
		li $v0, 4
		la $a0, promptMessage2 # Prompt the user to enter a value.
		syscall
		
		li $v0, 5 # Get a value from the user.
		syscall
		
		sw $v0, ($v1) # Store user input value into array.
		
		add $v1, $v1, $t2 # Move array address by adding $t2.
		add $t3, $t3, $t2 # Increasing $t3 by adding $t2.
		addi $s1, $s1, 1 # Increasing $s1 by adding 1.
		
		j loop # Go to loop.
	exit:
		sub $v1, $v1, $t3 # Initializing array address.
		add $t2, $zero, $zero # Initializing $t2.
		add $t3, $zero, $zero # Initializing $t3.
		add $s1, $zero, $zero # Initializing $s1.
		
		jr $ra # Go back to main function.
		
	printArrayElements:
		
		li $v0, 4
		la $a0, resultMessage # Show result message.
		syscall
		
	loop2:
		beq $t1, $s0, exit2 # Case: $t1 = $s0 -> go to exit2.
		
		lw $t2, ($t0) # Store the array element into $t2.
		
		li $v0, 1
		move $a0, $t2 # Print out $t2.
		syscall
		
		li $v0, 4
		la $a0, space # Print out space character.
		syscall
		
		addi $t0, $t0, 4 # Move array address by adding 4.
		addi $t1, $t1, 1 # Increasing $t1 by adding 1.
		
		j loop2 # Go to loop2.
	exit2:
		jr $ra # Go back to main function.
	
	bubbleSort:
		
		move $t0, $v1 # Move array address into $t0.
		
		add $t3, $zero, $zero # ouuter loop counter value
		subi $s1, $s0, 1 # outter loop condition value

	outterLoop:
		
		bge $t3, $s1, exit3 # Case: $t3 = $s1 -> go to exit3.
		add $t4, $zero, $zero # inner loop counter value
		sub $s2, $s1, $t3 # inner loop condition value
	
	innerLoop:
		
		bge $t4, $s2, exit5 # Case: $t4 = $s2 -> go to exit5.
	
		lw $t1, ($t0) # Store the array element into $t1.
		addi $t0, $t0, 4 # Move array address by adding 4.
		lw $t2, ($t0) # Store the array element into $t2.
		
		ble $t1, $t2, exit4 # Case: $t1 <= $t2 -> go to exit4.
	#############SWAP#############
		subi $t0, $t0, 4
		sw $t2, ($t0)
		addi $t0, $t0, 4
		sw $t1, ($t0)
	##############################
	exit4:	
		addi $t4, $t4, 1 # Increasing $t4 by adding 1.
		
		j innerLoop # Go to innerLoop.
	exit5:
		addi $t3, $t3, 1 # Increasing $t3 by adding 1.
		mul $t5, $t4, 4 # Register for initializing array address.
		sub $t0, $t0, $t5 # Initializing array address.
		 
		j outterLoop # Go to outterLoop.
	exit3:
		add $t1, $zero, $zero # Initializing $t1.
		
		jr $ra # Go back to main function.