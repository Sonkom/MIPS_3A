//Code concernant la traduction des instructions MIPS en leurs formes hexadécimales
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


int translate(char* line);

/*--------- GENERAL ---------*/
int translate_immediat(int code, int r0, int r1, int imm);

int translate_direct(int special, int r0, int r1, int r2, int r3, int code);

int translate_jump(int code, int adress);

/*--------- DIRECT ---------*/
int translate_ADD(int rd, int rs, int rt);
int translate_AND(int rd, int rs, int rt);
int translate_JR(int rs, int hint);
int translate_MFHI(int rd);
int translate_MFLO(int rd);
int translate_MULT(int rs, int rt);
int translate_NOP();
int translate_OR(int rd, int rs, int rt);
int translate_DIV(int rs, int rt);
int translate_ROTR(int rd, int rt, int sa);
int translate_SLL(int rd, int rt, int sa);
int translate_SLT(int rd, int rs, int rt);
int translate_SRL(int rd, int rt, int sa);
int translate_SUB(int rd, int rs, int rt);
int translate_XOR(int rd, int rs, int rt);

/*--------- IMMÉDIAT ---------*/
int translate_ADDI(int rt, int rs, int imm);
int translate_BEQ(int rs, int rt, int offset);
int translate_BGTZ(int rs, int offset);
int translate_BLEZ(int rs, int offset);
int translate_BNE(int rs, int rt, int offset);
int translate_LUI(int rt, int imm);
int translate_SW(int rt, int offset, int base);
int translate_LW(int rt, int offset, int base);

/*--------- JUMP ---------*/
int translate_J(int instr_index);
int translate_JAL(int instr_index);

/*--------- ? ---------*/
int translate_SYSCALL(int code);
