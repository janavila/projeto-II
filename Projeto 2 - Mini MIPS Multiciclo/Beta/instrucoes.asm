addi $r2, $0, 5
addi $r1, $0, 3
add $r3, $r2, $r1
add $r3, $r2, $r1
addi $r4, $0, 10
sw $r2, 0($0)
lw $r1, 4($0)
beq $r2, $0, 8
beq $r5, $0, 1
beq $r2, $r3, 10
beq $r2, $0, -1
beq $r2, $0, -2
beq $r2, $0, -3
beq $r2, $0, -4
beq $r2, $0, -5
beq $r2, $0, -6
j 1
