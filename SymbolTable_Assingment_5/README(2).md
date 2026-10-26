# Symbol Table

This is a C program that generates a symbol table from an assembly language program. 
It reads assembly instructions and data declarations, identifies symbols, calculates their sizes and addresses, and displays the symbol table.
The program uses an opcode file to identify supported instructions.

# Steps
- Read an assembly language program from 'assembly.asm'.
- Read instruction details from 'opcode.txt'.
- Identify symbols and labels.
- Calculate the size and address of each symbol.
- Display the symbol table in a tabular format.
- Identify undefined symbols and display error messages.

Symbol_Table/
├── symbol_table.c
├── assembly.asm
├── opcode.txt
├── output.png
└── README.md

