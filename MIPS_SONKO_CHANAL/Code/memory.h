#include "translation.h"
#include "function.h"
#include "file.h"

#define NBR_REGISTERS 35

int registers[NBR_REGISTERS]; /* Tableau des registres : de $0 à $31 + hi, lo et pc respectivement à 33, 34 et 35;*/

/*---- TRADUCTION DES REGISTRES ----*/

int* zero = registers+0; /* Registre ZERO (toujours nul) */
int* at = registers+1;  /* Assembler tempory*/
// Retour d'une sous-routine :
int* v0 = registers+2;
int* v1 = registers+3;
// Arguments d'une sous-routine :
int* a0 = registers+4;
int* a1 = registers+5;
int* a2 = registers+6;
int* a3 = registers+7;
// Registres temporaires
int* t0 = registers+8;
int* t1 = registers+9;
int* t2 = registers+10;
int* t3 = registers+11;
int* t4 = registers+12;
int* t5 = registers+13;
int* t6 = registers+14;
int* t7 = registers+15;
// Registres temporaires préservés par les sous-routines
int* s0 = registers+16;
int* s1 = registers+17;
int* s2 = registers+18;
int* s3 = registers+19;
int* s4 = registers+20;
int* s5 = registers+21;
int* s6 = registers+22;
int* s7 = registers+23;
// Deux temporaires supplémentaires
int* t8 = registers+24;
int* t9 = registers+25;
// Kernel (réservés !)
int* k0 = registers+26;
int* k1 = registers+27;

int* gp = registers+28; /* Global Pointer */
int* sp = registers+29; /* Stack Pointer */
int* fp = registers+30; /* Frame Pointer */
int* ra = registers+31; /* Return Adress */
// Registres de stockage pour des opérations entre deux données de 32 bits;
int* hi = registers+32;
int* lo = registers+33;

int* pc = registers+34; /* PROGRAM COUNTER */

//void init_registers(void);
