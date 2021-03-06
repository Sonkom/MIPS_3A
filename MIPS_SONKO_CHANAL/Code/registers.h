//Gère le processeur (registre + exécution d'instruction)

#include "memory.h"

#define NBR_REGISTERS 35
#define MAX_SIGNED_INT 32767
#define MIN_SIGNED_INT -32768

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
int exec_ADD(int instruction);
int exec_AND(int instruction);
int exec_JR(int instruction);
int exec_MFHI(int instruction);
int exec_MFLO(int instruction);
int exec_MULT(int instruction);
int exec_NOP(int instruction);
int exec_OR(int instruction);
int exec_DIV(int instruction);
int exec_ROTR(int instruction);
int exec_SLL(int instruction);
int exec_SLT(int instruction);
int exec_SRL(int instruction);
int exec_SUB(int instruction);
int exec_XOR(int instruction);

/*--------- IMMÉDIAT ---------*/
int exec_ADDI(int instruction);
int exec_BEQ(int instruction);
int exec_BGTZ(int instruction);
int exec_BLEZ(int instruction);
int exec_BNE(int instruction);
int exec_LUI(int instruction);
int exec_SW(int instruction);
int exec_LW(int instruction);

/*--------- JUMP ---------*/
int exec_J(int instruction);
int exec_JAL(int instruction);

/*--------- OPT ---------*/
int exec_ADDIU(int instruction);
int exec_ADDU(int instruction);
int exec_BGEZ(int instruction);
int exec_BGEZAL(int instruction);
int exec_BLTZ(int instruction);
int exec_BLTZAL(int instruction);
int exec_SUBU(int instruction);

int exec_SYSCALL(int instruction);
