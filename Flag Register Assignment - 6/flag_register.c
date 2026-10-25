#include <stdio.h>
#include <string.h>
#include <stdint.h>

void display_flags(uint8_t a, uint8_t b, char op[])
{
    uint8_t result = 0;
    unsigned int carry = 0;
    int overflow = 0;

    if (strcmp(op, "ADD") == 0)
    {
        unsigned int sum = (unsigned int)a + b;

        result = (uint8_t)sum;
        carry = (sum > 255);

        overflow = ((~(a ^ b) & (a ^ result) & 0x80) != 0);
    }
    else if (strcmp(op, "SUB") == 0 ||
             strcmp(op, "CMP") == 0)
    {
        result = (uint8_t)(a - b);
        carry = (a < b);

        overflow = (((a ^ b) & (a ^ result) & 0x80) != 0);
    }
    else if (strcmp(op, "AND") == 0)
    {
        result = a & b;
    }
    else if (strcmp(op, "OR") == 0)
    {
        result = a | b;
    }
    else if (strcmp(op, "XOR") == 0)
    {
        result = a ^ b;
    }
    else
    {
        printf("Invalid instruction!\n");
        return;
    }

    int zero_flag = (result == 0);
    int sign_flag = ((result & 0x80) != 0);


    int count = 0;

    for (int i = 0; i < 8; i++)
    {
        if (result & (1u << i))
        {
            count++;
        }
    }

    int parity_flag = (count % 2 == 0);

    printf("\nInstruction: %s %u, %u\n", op, a, b);

    if (strcmp(op, "CMP") != 0)
    {
        printf("Result: %u (0x%02X)\n", result, result);
    }
    else
    {
        printf("Comparison result: %s\n",
               (a == b) ? "Equal" : "Not equal");
    }

    printf("\nFlag Register\n");
    printf("CF (Carry Flag)     = %d\n", carry);
    printf("ZF (Zero Flag)      = %d\n", zero_flag);
    printf("SF (Sign Flag)      = %d\n", sign_flag);
    printf("OF (Overflow Flag)  = %d\n", overflow);
    printf("PF (Parity Flag)    = %d\n", parity_flag);
}

int main(void)
{
    char op[10];
    unsigned int a, b;

    printf("FLAG REGISTER\n");

    printf("\nInstructions : \n");
    printf("ADD, SUB, CMP, AND, OR, XOR\n");

    printf("\nEnter Instruction : ");

    if (scanf("%9s", op) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    
    for (int i = 0; op[i] != '\0'; i++)
    {
        if (op[i] >= 'a' && op[i] <= 'z')
        {
            op[i] = op[i] - 'a' + 'A';
        }
    }

    printf("Enter first operand (0-255): ");

    if (scanf("%u", &a) != 1 || a > 255)
    {
        printf("Invalid operand! Enter a number from 0 to 255.\n");
        return 1;
    }

    printf("Enter second operand (0-255): ");

    if (scanf("%u", &b) != 1 || b > 255)
    {
        printf("Invalid operand! Enter a number from 0 to 255.\n");
        return 1;
    }

    display_flags((uint8_t)a, (uint8_t)b, op);

    return 0;
}
