//Gère le processeur (registre + exécution d'instruction)

#include "memory.h"

#define NBR_REGISTERS 35

char* registers_name[NBR_REGISTERS];
int registers[NBR_REGISTERS]; /* Tableau des registres : de $0 à $31 + hi, lo et pc respectivement à 33, 34 et 35;*/

// Registres de stockage pour des opérations entre deux données de 32 bits;
int* hi;
int* lo;

int* pc; /* PROGRAM COUNTER */

/* ------ Manipulations des registres ------ */

void init_registers(void); //Permet d'initialiser les tableaux globaux ainsi que les pointeurs

void print_registers(void); //Affiche l'état actuel des registres

int read_register(int index_register); //Retourne le registre d'indice index_register

void write_register(int index_register, int value);//Change la valeur du registre d'indice index_register


//Fonctions d'exécution pour chaque opérations :
void exec_ADD(int instruction);
void exec_AND(int instruction);
void exec_JR(int instruction);
void exec_MFHI(int instruction);
void exec_MFLO(int instruction);
void exec_MULT(int instruction);
void exec_NOP(int instruction);
void exec_OR(int instruction);
void exec_DIV(int instruction);
void exec_ROTR(int instruction);
void exec_SLL(int instruction);
void exec_SLT(int instruction);
void exec_SRL(int instruction);
void exec_SUB(int instruction);
void exec_XOR(int instruction);

/*--------- IMMÉDIAT ---------*/
void exec_ADDI(int instruction);
void exec_BEQ(int instruction);
void exec_BGTZ(int instruction);
void exec_BLEZ(int instruction);
void exec_BNE(int instruction);
void exec_LUI(int instruction);
void exec_SW(int instruction);
void exec_LW(int instruction);

/*--------- JUMP ---------*/
void exec_J(int instruction);
void exec_JAL(int instruction);

/*--------- OPT ---------*/
void exec_ADDIU(int instruction);
void exec_ADDU(int instruction);
void exec_ANDI(int instruction);
void exec_BGEZ(int instruction);
void exec_BGEZAL(int instruction);
void exec_BLTZ(int instruction);
void exec_BLTZAL(int instruction);
void exec_DIVU(int instruction);
void exec_LB(int instruction);
void exec_MULTU(int instruction);
void exec_ORI(int instruction);
void exec_SB(int instruction);
void exec_SLLV(int instruction);
void exec_SLTI(int instruction);
void exec_SLTIU(int instruction);
void exec_SLTU(int instruction);
void exec_SRA(int instruction);
void exec_SRLV(int instruction);
void exec_SUBU(int instruction);
void exec_XORI(int instruction);
