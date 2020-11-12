//Gère le processeur (registre + exécution d'instruction)

#include "memory.h"

#define NBR_REGISTERS 35

char* registers_name[NBR_REGISTERS];
int registers[NBR_REGISTERS]; /* Tableau des registres : de $0 à $31 + hi, lo et pc respectivement à 33, 34 et 35;*/

/*---- TRADUCTION DES REGISTRES ----*/

int* gp; /* Global Pointer */
int* sp; /* Stack Pointer */
int* fp; /* Frame Pointer */
int* ra; /* Return Adress */
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
void exec_ADDI(int instruction);
void exec_AND(int instruction);
void exec_BEQ(int instruction);
