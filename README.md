# Command Pipeline Model
Coursework on computer architecture

## Task Description

### Estimation of the average command execution time

The processor pipeline includes the following steps: 
* read command code
* decode command code
* select first operand
* select second operand
* calculate result
* write data (at the address of the second operand)

Decoding operation takes 1 clock cycle.

### Adressing operands

Two ways of adressing:
* register
* indirect

Register adressing probability for current command:
+ P1 (0.9; 0.8; 0.6) 

Register accessing time:
+ 1 clock cycle

Memory accessing time:
+ N clock cycles (2, 5, 10)

Both the command code and the operand are word in memory.

### Command types

Two types of commands are used.
Calculation of the result for commands of the first type is performed in 1 clock cycle, calculation of the result for commands of the second type is performed in M clock cycles (4, 8, 16).
The probability that the current command is a command of the first type is P2 (0.9; 0.7; 0.5).
At one moment it can be executed:
* read and write from registers
* one read command and one decode command or calculating result