#include <string.h>
#include <ctype.h>

#include "operand.h"

int isRegister(char *operand)
{
    if (strcmp(operand, "EAX") == 0 ||
        strcmp(operand, "EBX") == 0 ||
        strcmp(operand, "ECX") == 0 ||
        strcmp(operand, "EDX") == 0 ||
        strcmp(operand, "ESP") == 0 ||
        strcmp(operand, "EBP") == 0 ||
        strcmp(operand, "ESI") == 0 ||
        strcmp(operand, "EDI") == 0)
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


        if (i == len - 1 && (operand[i] == 'H' || operand[i] == 'h'))
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
