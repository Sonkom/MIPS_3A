//Gère la mémoire de données

#include "translation.h"

typedef struct cell cell;

struct cell {
  unsigned int address; /* Addresse de l'instruction */
  char data ; /* contenue de la cellule */
  cell* next ; /* adresse du successeur */
};

cell* data_memory;

/*------ FONCTIONS POUR LA MÉMOIRE DE DONNÉES ------*/

void init_data_memory(void); //Initialise la liste chainée correspondant à la mémoire de donnée

cell* add_cell(int address, char data); //Ajoute un champ dans la mémoire de donnée d'adresse passée en argument

void write_data(unsigned int address, int data); //Écris dans la mémoire de donnée le mot "data" à la case mémoire d'adresse "address" (Instruction Store Word)

int read_data(unsigned int address); //Lis le mot présent à la case mémoire d'adresse "address"

//void write_data_char(cell* write, unsigned int address, char* data_bytes);
