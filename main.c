#include <stdio.h>

#include "parser.h"


int main()
{
    FILE *fp;
    char line[200];
    int lineNumber = 1;

    
    fp = fopen("assembly.asm", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open assembly.asm\n");
        return 1;
    }

 
    printf("OPCODE CHECK PROGRAM\n");
    
    while (fgets(line, sizeof(line), fp))
    {
        processLine(line, lineNumber);

        lineNumber++;
    }


    fclose(fp);

    printf("CHECKING COMPLETED\n");
 
    return 0;
}
