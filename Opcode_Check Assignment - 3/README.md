Opcode Check Assignment

1] Assignment Overview

The Opcode Check Project is a C-based program designed to read and process assembly language instructions using an opcode table.
The project is divided into different modules, with each team member responsible for developing a specific part of the system. 
All the individual modules are then integrated to create the complete working program.

2] Team Members and Responsibilities

1. Namita Ghodke — Opcode Reader

Responsibilities:
  - Reads the opcode table from "opcode.txt".
  - Searches for the mnemonic provided by the parser.
  - Checks whether the given mnemonic is present in the opcode table.
  - Returns the corresponding opcode information when the mnemonic is found.

Branch: "namita-opcode"

Code Files:
  - "opcode_reader.h"
  - "opcode_reader.c"

GitHub: https://github.com/namita-ghodke13


2. Shital Dudhade — Operand Handling

Responsibilities:
  - Handles the operands used with assembly instructions.
  - Performs operand-related processing.
  - Checks and validates the operands according to the instruction requirements.

Branch: "shital-operand"

Code Files:
  - operand.h
  - operand.c

GitHub: https://github.com/shital0101


3. Vaishnavi Shinde — Parser

Responsibilities:
  - Reads and parses the assembly language instructions.
  - Separates the instruction into its different components, such as mnemonic and operands.
  - Passes the required information to the appropriate modules for further processing.

Branch: "vaishnavi-parser"

Code Files:
  - parser.h
  - parser.c

GitHub: https://github.com/vaishnavishinde1722


4. Kaveri Patare — Main Program

Responsibilities:
  - Controls the overall execution of the program.
  - Connects and integrates the different modules.
  - Takes the input assembly file and coordinates the processing of instructions.
  - Displays the final output.

Branch: "kaveri-main"

Code Files:
  - main.c

GitHub: https://github.com/kaveripatare218


3] GitHub Branches

The project is developed using separate branches for each major module:

1. "main" — Final integrated project
2. "namita-opcode" — Opcode Reader
3. "shital-operand" — Operand Handling
4. "vaishnavi-parser" — Parser
5. "kaveri-main" — Main Program

This branch structure allows each team member to work independently on their assigned module before integrating the code into the main 
project.

4] Program Execution Flow

The overall flow of the program is:

assembly.asm
      ↓
Main Program
      ↓
    Parser
      ↓
Opcode Reader
      ↓
Operand Handling
      ↓
Final Output

The input assembly file is first handled by the main program. The parser breaks each instruction into its required components. 
The opcode reader then checks the mnemonic against the opcode table, while the operand module processes and validates the operands. 
Finally, the results are displayed as the program output.

5] Input Files

The project uses the following input files:

- "assembly.asm" — Contains the assembly language instructions that need to be processed.
- "opcode.txt" — Contains the opcode table used to find and verify instruction mnemonics.

6] GitHub Repository

Repository: https://github.com/namita-ghodke13/Opcode-Check
