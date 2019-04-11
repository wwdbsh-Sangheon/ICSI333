# Name: Sangheon Lee
# Student ID Number: 001286825
.data
	promptMessage: .asciiz "User Enters: "
	resultMessage: .asciiz "Output: "
	
.text

	main:
		# Displaying prompt message.
		li $v0, 4
		la $a0, promptMessage
		syscall
	
		# Prompt the user to enter a decimal number.
		li $v0, 5
		syscall
		
		add $s1, $zero, $v0
		
		# Displaying result message.
		li $v0, 4
		la $a0, resultMessage
		syscall
		
		# Go to 'convertingNumber' function.
		jal convertingNumber
		
	end:
		# Finish the program.
		li $v0, 10
		syscall
	
	convertingNumber:
		
		add $t0, $zero, $s1 # Put user's input value into $t0.
		add $t1, $zero, $zero # Initially set $t1, which will be printed out on the console, to 0.
		addi $t2, $zero, 1 # Set $t2 to 1 (1 is 000...001 as a binary number).
		addi $t3, $zero, 32 # Loop counter
		sll $t2, $t2, 31 # Make 10000000000000000000000000000000(form of 32-bits binary) to combine with user's input value.
		
	Loop1:
		and $t1, $t0, $t2 # Combine $t2 with $t0(user's input value) by using 'and' statement.
		beq $t1, $zero, print # If $t1 is 0, go to 'print' function and then print 0.
		
		# If $t1 is not 0, set $t1 to 1 and then print 1.
		add $t1, $zero, $zero
		addi $t1, $zero, 1
	
	print:
		# Print $t1 which is decided above part.
		li $v0, 1
		add $a0, $zero, $t1
		syscall
		
		srl $t2, $t2, 1 # Shift 32-bits binary numbers of $t2 to the right by 1.
		addi $t3, $t3, -1 # Loop counter - 1.
		beq $t3, $zero, end # If $t3(loop counter) is 0, go to 'end.'
		
		j Loop1 # Go back to Loop1.
