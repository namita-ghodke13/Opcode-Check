**Introduction**

This code is written in C. 
It scans all the .c files in a folder and reads the comments from each file. 
It extracts the file name and its description and displays them in a table.

------------------------------------------------------------------------------------------

**Compile**

gcc filename.c

example::

gcc task.c

--------------------------------------------------------------------------------------------

**Execution**

./a.out directory path

./a.out /home/user/shital/nasm-master/asm

--------------------------------------------------------------------------------------------

**output**


+-----+----------------------+-----------------------------------------------+
| No. | File Name            | Description                                   |
+-----+----------------------+-----------------------------------------------+
| 1   | assemble.c           | code generation for the Netwide Assembler     |
| 2   | exprdump.c           |                                               |
| 3   | error.c              | - error message handling routines for the assembler |
| 4   | parser.c             | source line parser for the Netwide Assembler  |
| 5   | eval.c               | expression evaluator for the Netwide Assembler |
| 6   | quote.c              |                                               |
| 7   | exprlib.c            |                                               |
| 8   | preproc.c            | macro preprocessor for the Netwide Assembler  |
| 9   | srcfile.c            | - keep track of the current position in the input stream. |
| 10  | labels.c             | label handling for the Netwide Assembler      |
| 11  | rdstrnum.c           |                                               |
| 12  | strfunc.c            |                                               |
| 13  | listing.c            | listing file generator for the Netwide Assembler |
+-----+----------------------+-----------------------------------------------+
