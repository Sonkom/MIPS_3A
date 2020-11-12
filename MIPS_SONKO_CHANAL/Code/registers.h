//Gère le processeur (registre + exécution d'instruction)

#include "memory.h"

#define NBR_REGISTERS 35

char* registers_name[NBR_REGISTERS];
int registers[NBR_REGISTERS]; /* Tableau des registres : de $0 à $31 + hi, lo et pc respectivement à 33, 34 et 35;*/

/*---- TRADUCTION DES REGISTRES ----*/

int* zero; /* Registre ZERO (toujours nul) */
int* at;  /* Assembler tempory*/
// Retour d'une sous-routine :
int* v0;
int* v1;
// Arguments d'une sous-routine :
int* a0;
int* a1;
int* a2;
int* a3;
// Registres temporaires
int* t0;
int* t1;
int* t2;
int* t3;
int* t4;
int* t5;
int* t6;
int* t7;
// Registres temporaires préservés par les sous-routines
int* s0;
int* s1;
int* s2;
int* s3;
int* s4;
int* s5;
int* s6;
int* s7;
// Deux temporaires supplémentaires
int* t8;
int* t9;
// Kernel (réservés !)
int* k0;
int* k1;

int* gp; /* Global Pointer */
int* sp; /* Stack Pointer */
int* fp; /* Frame Pointer */
int* ra; /* Return Adress */
// Registres de stockage pour des opérations entre deux données de 32 bits;
int* hi;
int* lo;

int* pc; /* PROGRAM COUNTER */

void init_registers(void);

void print_registers(void);

int read_register(int index_register);

void write_register(int index_register, int value);

void exec_ADD(int instruction);
void exec_ADDI(int instruction);
void exec_AND(int instruction);
void exec_BEQ(int instruction);
