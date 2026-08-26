#ifndef OPERAND_H
#define OPERAND_H

int isRegister(char *operand);
int isConstant(char *operand);
int isMemory(char *operand);
int isSymbol(char *operand);

char *getOperandType(char *operand);

#endif
