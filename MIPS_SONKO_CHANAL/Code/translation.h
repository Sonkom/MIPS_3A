//Code concernant la traduction des instructions MIPS en leurs formes hexadécimales
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Type de code :
  - Immediat  : ADDI, BEQ, BGTZ, BLEZ, BNE, LUI, LW, SW
  - Direct : ADD, AND, JR, MFHI, MFLO, MULT, NOP, OR, SLL, DIV, ROTR, SLL, SLT, SRL, SUB, XOR
  - Jump : J, JAL
  - ? : SYSCALL
*/

int translate(char* line);

/*--------- GENERAL ---------*/
int translate_immediat(int code, int r0, int r1, int imm);

int translate_direct(int special, int r0, int r1, int r2, int r3, int code);

int translate_jump(int code, int adress);

/*--------- DIRECT ---------*/
int translate_ADD(int rs, int rt, int rd);
int translate_AND(int rs, int rt, int rd);
int translate_JR(int rs, int hint);
int translate_MFHI(int rd);
int translate_MFLO(int rd);
int translate_MULT(int rs, int rt);
int translate_NOP(void);
int translate_OR(int rs, int rt, int rd);
int translate_DIV(int rs, int rt);
int translate_ROTR(int ri, int rt, int rd, int sa);
int translate_SLL(int rt, int rd, int sa);
int translate_SLT(int rs, int rt, int rd);
int translate_SRL(int r0, int rt, int rd, int sa);
int translate_SUB(int rs, int rt, int rd);
int translate_XOR(int rs, int rt, int rd);

/*--------- IMMÉDIAT ---------*/
int translate_ADDI(int rs, int rt, int imm);
int translate_BEQ(int rs, int rt, int offset);
int translate_BGTZ(int rs, int offset);
int translate_BLEZ(int rs, int offset);
int translate_BNE(int rs, int rt, int offset);
int translate_LUI(int rt, int imm);
int translate_SW(int base, int rt, int offset);
int translate_LW(int base, int rt, int offset);

/*--------- JUMP ---------*/
int translate_J(int instr_index);
int translate_JAL(int instr_index);

/*--------- ? ---------*/
int translate_SYSCALL(int code);
