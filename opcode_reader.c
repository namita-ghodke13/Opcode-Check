#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "opcode_reader.h"

#define MAX_LINE 200
#define MAX_MNEMONIC 20


static void upperCase(char *str)
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
