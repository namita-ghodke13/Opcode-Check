**Introduction**

This code is written in c.
It scans all the .c files in a folder and reads the comments from each file.
It extracts the file name and its description and display them in a table.

---------------------------------------------------------------------------------------
**Compile**

gcc filename.c

example::

gcc task3.c

-----------------------------------------------------------------------------------------

**Execution**

./a.out directory path

./a.out /home/kaveri/local/nasm-master/asm

------------------------------------------------------------------------------------------

**Output**

----------------------------------------------------------------------------------------------------------
| Filename                       | Description                                                  |
----------------------------------------------------------------------------------------------------------
| pptok.c                        | #include "compiler.h"                                        |
| uncompress.c                   | This needs to be in a separate file because zlib.h conflicts |
| getbool.c                      | 1. An expression (true if nonzero 0)                         |
| srcfile.c                      | keep track of the current position in the input stream.      |
| preproc.c                      | macro preprocessor for the Netwide Assembler                 |
| quote.c                        |                                                              |
| stdscan.c                      | and some output                                              |
| strfunc.c                      |                                                              |
| listing.c                      | listing file generator for the Netwide Assembler             |
| rdstrnum.c                     |                                                              |
| parser.c                       | source line parser for the Netwide Assembler                 |
| exprlib.c                      |                                                              |
| tokhash.c                      | This file is generated from insns.dat, regs.dat and token.dat |
| nasm.c                         | The Netwide Assembler main program module                    |
| eval.c                         | expression evaluator for the Netwide Assembler               |
| error.c                        | error message handling routines for the assembler            |
| assemble.c                     | code generation for the Netwide Assembler                    |
| directbl.c                     | This file is generated from ./asm/directiv.dat               |
| directiv.c                     | Parse and handle assembler directives                        |
| labels.c                       | label handling for the Netwide Assembler                     |
| segalloc.c                     | library routines for the Netwide Assembler                   |
| pragma.c                       | Parse and handle [pragma] directives.  The preprocessor handles |
| warnings.c                     | Description not found                                        |
| exprdump.c                     |                                                              |
| floats.c                       | floating-point constant support for the Netwide Assembler    |
----------------------------------------------------------------------------------------------------------
