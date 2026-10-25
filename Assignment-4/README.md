# Little Endian Conversion Assignment

This Assignment is written in C. 
It reads data declarations from an assembly file and converts the given values into hexadecimal representation and Little Endian format.

# Process
- Read data from an assembly (.asm) file.
- Identify strings enclosed in single or double quotes.
- Convert string characters into ASCII values and hexadecimal.
- Convert numeric values into hexadecimal.
- Display numeric values in Little Endian format.

# Files
- assembler_v2.c – C source code.
- input.asm – Input assembly program.
- output.png – Sample output.

# Input Example
.asm 

a dd 10
b db "Hello"
c db 'A'
