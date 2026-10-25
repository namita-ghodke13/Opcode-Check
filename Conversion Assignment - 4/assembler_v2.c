#include <stdio.h>
#include <string.h>
#include <ctype.h>

void processString(char *str)
{
    int i;

    printf("String : %s\n", str);

    printf("ASCII : ");
    for (i = 0; str[i] != '\0'; i++)
    {
        printf("%d ", (unsigned char)str[i]);
    }

    printf("\nHex : ");
    for (i = 0; str[i] != '\0'; i++)
    {
        printf("%02X ", (unsigned char)str[i]);
    }

    printf("\n\n");
}

void processNumber(unsigned int number)
{
    int i;

    printf("Decimal : %u\n", number);

    printf("Hexadecimal : %08X\n", number);

    printf("Little Endian Format : ");

    for (i = 0; i < 4; i++)
    {
        printf("%02X ", (number >> (i * 8)) & 0xFF);
    }

    printf("\n\n");
}

int main()
{
    FILE *file;
    char line[200];
    char *start;
    char *end;
    unsigned int number;

    file = fopen("input.asm", "r");

    if (file == NULL)
    {
        printf("Error: Cannot open input.asm\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        start = strchr(line, '"');

        if (start != NULL)
        {
            end = strchr(start + 1, '"');

            if (end != NULL)
            {
                *end = '\0';
                processString(start + 1);
                continue;
            }
        }

        start = strchr(line, '\'');

        if (start != NULL)
        {
            end = strchr(start + 1, '\'');

            if (end != NULL)
            {
                *end = '\0';
                processString(start + 1);
                continue;
            }
        }

        if (strstr(line, "dd") != NULL)
        {
            if (sscanf(strstr(line, "dd") + 2, "%u", &number) == 1)
            {
                processNumber(number);
            }
        }
    }

    fclose(file);

    return 0;
}
