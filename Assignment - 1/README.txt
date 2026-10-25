SOURCE CODE FILE ANALYSIS

Name      : Namita Vinayak Ghodke.
Roll No   : 25111019
Course    : M.Sc. Computer Science


Assignment Description : 

This program accepts a directory path from the user. It recursively scans the specified directory and all its subdirectories. The program processes only C source files (.c), extracts the program name and its description from the initial comment block of each file, displays the information on the screen, and stores the same output in output.txt.


Files Submitted :

1. program.c   - Source code
2. README.txt  - Documentation
3. output.txt  - Generated output


Compilation : 

gcc program.c -o program

Execution :

./program


Input : 

Enter the directory path containing the source code files.


Example:

/home/namita/Downloads/nasm-master/asm


Output : 

The program displays the filename and its description.

Example:

assemble.c : code generation for the Netwide Assembler
error.c : error handling routines
listing.c : listing file generation

The same output is also saved in output.txt.

Functions Used :

opendir()   - Opens a directory.
readdir()   - Reads directory entries.
closedir()  - Closes the directory.
stat()      - Checks whether an entry is a file or directory.
fopen()     - Opens a file.
fgets()     - Reads a line from a file.
fprintf()   - Writes output to output.txt.
fclose()    - Closes the file.
strstr()    - Searches for a substring.
strrchr()   - Finds the file extension.
strcmp()    - Compares strings.
sprintf()   - Creates the complete file path.


Problems Faced :

1. Understanding recursive directory traversal.
2. Reading only .c files from the directory.
3. Extracting the program name and description from the comment block.
4. Generating output.txt automatically.
5. Handling nested directories.
