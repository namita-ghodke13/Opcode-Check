#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SYMBOLS 200
#define MAX_LINE 512

typedef struct
{
    int id;
    char name[64];
    int size;
    char value[256];
    char section;
    int address;
    char status;
} Symbol;

Symbol symbols[MAX_SYMBOLS];
int symbol_count = 0;

int data_address = 0;
int text_address = 0;
char current_section = 'T';


void uppercase(char *s);

#define MAX_OPCODE_MNEMONICS 100

char opcode_mnemonics[MAX_OPCODE_MNEMONICS][32];
int opcode_count = 0;


int load_opcode_table(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    char line[MAX_LINE];
    char mnemonic[32];

    if (fp == NULL) {
        printf("Error: Cannot open opcode file '%s'.\n", filename);
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%31s", mnemonic) != 1)
            continue;

        uppercase(mnemonic);

        int found = 0;
        for (int i = 0; i < opcode_count; i++) {
            if (strcmp(opcode_mnemonics[i], mnemonic) == 0) {
                found = 1;
                break;
            }
        }

        if (!found && opcode_count < MAX_OPCODE_MNEMONICS) {
            snprintf(opcode_mnemonics[opcode_count],
                     sizeof(opcode_mnemonics[opcode_count]),
                     "%s", mnemonic);
            opcode_count++;
        }
    }

    fclose(fp);
    return opcode_count > 0;
}


int is_instruction(const char *word)
{
    char temp[64];

    if (strlen(word) >= sizeof(temp))
        return 0;

    snprintf(temp, sizeof(temp), "%s", word);
    uppercase(temp);

    for (int i = 0; i < opcode_count; i++) {
        if (strcmp(temp, opcode_mnemonics[i]) == 0)
            return 1;
    }

    return 0;
}

void trim(char *s)
{
    int start = 0;
    int end;

    while (isspace((unsigned char)s[start]))
        start++;

    if (start > 0)
        memmove(s, s + start, strlen(s + start) + 1);

    end = (int)strlen(s) - 1;

    while (end >= 0 && isspace((unsigned char)s[end]))
        s[end--] = '\0';
}

void uppercase(char *s)
{
    int i;
    for (i = 0; s[i]; i++)
        s[i] = (char)toupper((unsigned char)s[i]);
}

void remove_comment(char *s)
{
    char quote = '\0';
    int i;

    for (i = 0; s[i]; i++)
    {
        if (quote != '\0' && s[i] == '\\' && s[i + 1])
        {
            i++;
            continue;
        }

        if (s[i] == '\'' || s[i] == '"')
        {
            if (quote == '\0')
                quote = s[i];
            else if (quote == s[i])
                quote = '\0';
        }
        else if (s[i] == ';' && quote == '\0')
        {
            s[i] = '\0';
            return;
        }
    }
}


int directive_size(const char *directive)
{
    if (strcmp(directive, "DB") == 0) return 1;
    if (strcmp(directive, "DW") == 0) return 2;
    if (strcmp(directive, "DD") == 0) return 4;
    if (strcmp(directive, "DQ") == 0) return 8;
    if (strcmp(directive, "DT") == 0) return 10;

    return 0;
}


int calculate_size(const char *value, int unit)
{
    int total = 0;
    int i = 0;
    int start = 0;
    int len = (int)strlen(value);
    char quote = '\0';

    while (i <= len)
    {
        if (value[i] == '\'' || value[i] == '"')
        {
            if (quote == '\0')
                quote = value[i];
            else if (quote == value[i])
                quote = '\0';
        }

        if ((value[i] == ',' && quote == '\0') ||
            value[i] == '\0')
        {
            char item[256];
            int n = i - start;

            if (n >= (int)sizeof(item))
                n = (int)sizeof(item) - 1;

            strncpy(item, value + start, n);
            item[n] = '\0';
            trim(item);

            if (item[0] != '\0')
            {
                int item_len = (int)strlen(item);

                if (unit == 1 &&
                    (item[0] == '\'' || item[0] == '"') &&
                    item_len >= 2 &&
                    item[item_len - 1] == item[0])
                {
                    total += item_len - 2;
                }
                else
                {
                    total += unit;
                }
            }

            start = i + 1;
        }

        i++;
    }

    return total;
}

int find_symbol(const char *name)
{
    int i;

    for (i = 0; i < symbol_count; i++)
    {
        if (strcmp(symbols[i].name, name) == 0)
            return i;
    }

    return -1;
}


void add_symbol(const char *name, int size, const char *value,
                char section, int address, char status)
{
    int index = find_symbol(name);

    if (index >= 0)
    {
        if (symbols[index].status == 'U' && status == 'D')
        {
            symbols[index].size = size;
            strcpy(symbols[index].value, value);
            symbols[index].section = section;
            symbols[index].address = address;
            symbols[index].status = 'D';
        }
        else if (status == 'D')
        {
            printf("Error: Duplicate symbol '%s'.\n", name);
        }
        return;
    }

    if (symbol_count >= MAX_SYMBOLS)
    {
        printf("Error: Symbol table is full.\n");
        return;
    }

    index = symbol_count++;

    symbols[index].id = index + 1;
    snprintf(symbols[index].name,
             sizeof(symbols[index].name), "%s", name);
    symbols[index].size = size;
    snprintf(symbols[index].value,
             sizeof(symbols[index].value), "%s", value);
    symbols[index].section = section;
    symbols[index].address = address;
    symbols[index].status = status;
}


int is_register(const char *word)
{
    const char *registers[] = {
        "EAX", "EBX", "ECX", "EDX", "ESI", "EDI",
        "ESP", "EBP", "AX", "BX", "CX", "DX",
        "AL", "AH", "BL", "BH", "CL", "CH",
        "DL", "DH", "SI", "DI", "SP", "BP",
        "CS", "DS", "ES", "FS", "GS", "SS"
    };

    int i;

    for (i = 0; i < (int)(sizeof(registers) /
                          sizeof(registers[0])); i++)
    {
        if (strcmp(word, registers[i]) == 0)
            return 1;
    }

    return 0;
}

int is_number(const char *word)
{
    char *end;
    if (*word == '\0')
        return 0;

    strtol(word, &end, 0);
    return *end == '\0';
}

void find_references(char *operand_text)
{
    int i = 0;

    while (operand_text[i] != '\0')
    {
        char name[64];
        int n = 0;

        if (isalpha((unsigned char)operand_text[i]) ||
            operand_text[i] == '_' ||
            operand_text[i] == '.')
        {
            while (isalnum((unsigned char)operand_text[i]) ||
                   operand_text[i] == '_' ||
                   operand_text[i] == '.')
            {
                if (n < (int)sizeof(name) - 1)
                    name[n++] = operand_text[i];

                i++;
            }

            name[n] = '\0';

            char upper_name[64];
            snprintf(upper_name, sizeof(upper_name), "%s", name);
            uppercase(upper_name);

            if (is_register(upper_name) ||
                is_instruction(upper_name) ||
                strcmp(upper_name, "BYTE") == 0 ||
                strcmp(upper_name, "WORD") == 0 ||
                strcmp(upper_name, "DWORD") == 0 ||
                strcmp(upper_name, "PTR") == 0)
                continue;

            if (!is_number(name) && find_symbol(name) < 0)
            {
                add_symbol(name, 0, "-", '-', -1, 'U');
            }
        }
        else
        {
            i++;
        }
    }
}

void process_line(char *line)
{
    char name[64], directive[16], value[256];
    char temp[MAX_LINE];
    char *colon, *p;
    int consumed = 0;
    int size;

    trim(line);
    if (line[0] == '\0')
        return;

    strcpy(temp, line);
    uppercase(temp);
    trim(temp);

    if (strcmp(temp, "SECTION .DATA") == 0 ||
        strcmp(temp, ".DATA") == 0)
    {
        current_section = 'D';
        return;
    }

    if (strcmp(temp, "SECTION .TEXT") == 0 ||
        strcmp(temp, ".TEXT") == 0)
    {
        current_section = 'T';
        return;
    }

    if (strcmp(temp, "SECTION .BSS") == 0 ||
        strcmp(temp, ".BSS") == 0)
    {
        current_section = 'B';
        return;
    }

  
    if (strncmp(temp, "GLOBAL ", 7) == 0 ||
        strncmp(temp, "EXTERN ", 7) == 0)
        return;

   
    colon = strchr(line, ':');

    if (colon != NULL)
    {
        char label[64];
        int n = (int)(colon - line);

        if (n > 0 && n < (int)sizeof(label))
        {
            strncpy(label, line, n);
            label[n] = '\0';
            trim(label);

            add_symbol(label, 0, "-", current_section,
                       current_section == 'D' ? data_address :
                       text_address, 'D');
        }

        memmove(line, colon + 1, strlen(colon + 1) + 1);
        trim(line);

        if (line[0] == '\0')
            return;
    }

    name[0] = directive[0] = value[0] = '\0';

    if (sscanf(line, "%63s %15s %n",
               name, directive, &consumed) >= 2)
    {
        uppercase(directive);

        size = directive_size(directive);

        if (size > 0)
        {
            p = line + consumed;
            trim(p);
            snprintf(value, sizeof(value), "%s", p);

            size = calculate_size(value, size);

            add_symbol(name, size,
                       value[0] ? value : "-",
                       current_section,
                       current_section == 'D' ? data_address :
                       text_address, 'D');

            if (current_section == 'D')
                data_address += size;

            return;
        }
    }

    {
        char mnemonic[32];
        char operands[MAX_LINE];
        int i;

        if (sscanf(line, "%31s %n", mnemonic, &i) >= 1)
        {
            uppercase(mnemonic);

            if (is_instruction(mnemonic) || strcmp(mnemonic, "JMP") == 0)
            {
                snprintf(operands, sizeof(operands), "%s",
                         line + (int)strlen(line));

                p = line;
                while (*p && !isspace((unsigned char)*p))
                    p++;
                while (*p && isspace((unsigned char)*p))
                    p++;

                snprintf(operands, sizeof(operands), "%s", p);

                if (operands[0] != '\0')
                    find_references(operands);

                if (current_section == 'T')
                    text_address += 4;
            }
        }
    }
}

void display_table(void)
{
    int i;
    char section_text[8];
    char address_text[24];

    printf("\n");
    printf("================================================================"
           "================================\n");
    printf("                              SYMBOL TABLE\n");
    printf("================================================================"
           "================================\n");

    printf("%-5s %-16s %-8s %-28s %-10s %-12s %-8s\n",
           "ID", "Name", "Size", "Value",
           "Section", "Address", "Status");

    printf("----------------------------------------------------------------"
           "--------------------------------\n");

    for (i = 0; i < symbol_count; i++)
    {
        if (symbols[i].section == 'D')
            strcpy(section_text, "D");
        else if (symbols[i].section == 'T')
            strcpy(section_text, "T");
        else if (symbols[i].section == 'B')
            strcpy(section_text, "B");
        else
            strcpy(section_text, "-");

        if (symbols[i].address < 0)
            strcpy(address_text, "-");
        else
            snprintf(address_text, sizeof(address_text),
                     "0x%X", (unsigned int)symbols[i].address);

        printf("%-5d %-16s %-8d %-28.28s %-10s %-12s %-8c\n",
               symbols[i].id,
               symbols[i].name,
               symbols[i].size,
               symbols[i].value,
               section_text,
               address_text,
               symbols[i].status);
    }

    printf("================================================================"
           "================================\n");
    printf("Data section size: %d bytes\n", data_address);
    printf("Text section size: %d bytes (4 bytes per instruction "
           "as specified in the notebook)\n", text_address);
    printf("Status: D = Defined, U = Undefined\n");
    printf("Section: D = Data, T = Text, B = BSS\n");

    for (i = 0; i < symbol_count; i++)
    {
        if (symbols[i].status == 'U')
        {
            printf("Error: Undefined symbol '%s'.\n",
                   symbols[i].name);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char line[MAX_LINE];
    const char *filename = argc > 1 ? argv[1] : "assembly.asm";
    const char *opcode_filename = argc > 2 ? argv[2] : "opcode.txt";

    if (!load_opcode_table(opcode_filename)) {
        fprintf(stderr, "Error: No instruction mnemonics loaded from '%s'.\\n",
                opcode_filename);
        return 1;
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Cannot open '%s'.\n", filename);
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        remove_comment(line);
        process_line(line);
    }

    fclose(fp);
    display_table();

    return 0;
}
