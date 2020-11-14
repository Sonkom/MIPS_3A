//Gère la mémoire de données

#include "translation.h"

typedef struct cell cell;

struct cell {
  unsigned int address; /* Addresse de l'instruction */
  char data ; /* contenue de la cellule */
  cell* next ; /* adresse du successeur */
};

cell* data_memory;

/*------ FONCTIONS DE GESTION DE LA LISTE CHAÎNÉE ------*/

void init_data_memory(void); //Initialise la liste chainée correspondant à la mémoire de donnée

cell* add_cell(int address, char data); //Ajoute un champ dans la mémoire de donnée d'adresse passée en argument

void print_memory(void); //Affiche l'état de la mémoire de donnée

void free_memory(void); //Libère la mémoire de donnée (en fin de programme)

/*------ FONCTIONS POUR LA MÉMOIRE DE DONNÉES ------*/

void write_data(unsigned int address, int data); //Écris dans la mémoire de donnée le mot "data" à la case mémoire d'adresse "address" (Instruction Store Word)

int read_data(unsigned int address); //Lis le mot présent à la case mémoire d'adresse "address"
