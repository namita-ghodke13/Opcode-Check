#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "opcode_reader.h"
#include "operand.h"

#define MAX_LINE 200
#define MAX_MNEMONIC 20
#define MAX_OPERAND 50

static void trim(char *str)
{
    int start = 0;
    int end;

    while (isspace((unsigned char)str[start]))
        start++;

    end = strlen(str) - 1;

    while (end >= start &&
           isspace((unsigned char)str[end]))
    {
        str[end] = '\0';
        end--;
    }

    if (start > 0)
        memmove(str, str + start, strlen(str + start) + 1);
}


static void upperCase(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        str[i] = toupper((unsigned char)str[i]);
}

void processLine(char *line, int lineNumber)
{
    char mnemonic[MAX_MNEMONIC];
    char operandPart[MAX_LINE];

    char operand1[MAX_OPERAND];
    char operand2[MAX_OPERAND];

    char *comma;

    int length;


    line[strcspn(line, "\r\n")] = '\0';

    trim(line);

    if (strlen(line) == 0)
        return;


    if (sscanf(line, "%19s%n", mnemonic, &length) != 1)
        return;

    upperCase(mnemonic);

    strcpy(operandPart, line + length);

    trim(operandPart);


    printf("\nLine %d\n", lineNumber);
    printf("-----------------------------\n");

    printf("Mnemonic : %s\n", mnemonic);


    if (mnemonicExists(mnemonic))
        printf("Exists   : YES\n");
    else
        printf("Exists   : NO\n");


    if (strlen(operandPart) == 0)
    {
        printf("Operand  : None\n");
        return;
    }

    comma = strchr(operandPart, ',');

    if (comma != NULL)
    {
        *comma = '\0';

        strcpy(operand1, operandPart);
        strcpy(operand2, comma + 1);

        trim(operand1);
        trim(operand2);


        printf("Operand 1: %s\n", operand1);
        printf("Type     : %s\n",
               getOperandType(operand1));


        printf("Operand 2: %s\n", operand2);
        printf("Type     : %s\n",
               getOperandType(operand2));
    }


    else
    {
        strcpy(operand1, operandPart);

        trim(operand1);

        printf("Operand  : %s\n", operand1);
        printf("Type     : %s\n",
               getOperandType(operand1));
    }
}
