#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 200
#define MAX_MNEMONIC 20
#define MAX_OPERAND 50


int isRegister(char *operand)
{
    char reg[20];

    strcpy(reg, operand);

    if (strcmp(reg, "EAX") == 0 ||
        strcmp(reg, "EBX") == 0 ||
        strcmp(reg, "ECX") == 0 ||
        strcmp(reg, "EDX") == 0 ||
        strcmp(reg, "ESP") == 0 ||
        strcmp(reg, "EBP") == 0 ||
        strcmp(reg, "ESI") == 0 ||
        strcmp(reg, "EDI") == 0)
    {
        return 1;
    }

    return 0;
}


int isConstant(char *operand)
{
    int i;
    int len = strlen(operand);

    if (len == 0)
        return 0;

    

    for (i = 0; i < len; i++)
    {
        if (isdigit((unsigned char)operand[i]))
            continue;

        
        if (i == len - 1 &&
            (operand[i] == 'H' || operand[i] == 'h'))
        {
            return 1;
        }

        return 0;
    }

    return 1;
}


int isMemory(char *operand)
{
    int len = strlen(operand);

    if (len >= 2 &&
        operand[0] == '[' &&
        operand[len - 1] == ']')
    {
        return 1;
    }

    return 0;
}



int isSymbol(char *operand)
{
    int i;
    int len = strlen(operand);

    if (len == 0)
        return 0;

 
    if (isRegister(operand) ||
        isConstant(operand) ||
        isMemory(operand))
    {
        return 0;
    }

 
    if (!(isalpha((unsigned char)operand[0]) ||
          operand[0] == '_'))
    {
        return 0;
    }

    for (i = 1; i < len; i++)
    {
        if (!(isalnum((unsigned char)operand[i]) ||
              operand[i] == '_'))
        {
            return 0;
        }
    }

    return 1;
}



void trim(char *str)
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


void upperCase(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        str[i] = toupper((unsigned char)str[i]);
}


int mnemonicExists(char *mnemonic)
{
    FILE *fp;
    char line[MAX_LINE];
    char tableMnemonic[MAX_MNEMONIC];

    fp = fopen("opcode.txt", "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open opcode.txt\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%19s", tableMnemonic) == 1)
        {
            upperCase(tableMnemonic);

            if (strcmp(mnemonic, tableMnemonic) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);

    return 0;
}

char *getOperandType(char *operand)
{
    if (isRegister(operand))
        return "Register";

    if (isMemory(operand))
        return "Memory";

    if (isConstant(operand))
        return "Constant";

    if (isSymbol(operand))
        return "Symbol";

    return "Unknown";
}

void processLine(char *line, int lineNumber)
{
    char mnemonic[MAX_MNEMONIC];
    char operandPart[MAX_LINE];

    char operand1[MAX_OPERAND];
    char operand2[MAX_OPERAND];

    char *comma;

    int count;


    line[strcspn(line, "\r\n")] = '\0';

    trim(line);

    if (strlen(line) == 0)
        return;


    if (sscanf(line, "%19s", mnemonic) != 1)
        return;

    upperCase(mnemonic);


    strcpy(operandPart, line);

    {
        char temp[MAX_MNEMONIC];
        int length;

        sscanf(line, "%19s%n", temp, &length);

        strcpy(operandPart, line + length);
        trim(operandPart);
    }

    printf("\nLine %d\n", lineNumber);

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


int main()
{
    FILE *fp;
    char line[MAX_LINE];
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
