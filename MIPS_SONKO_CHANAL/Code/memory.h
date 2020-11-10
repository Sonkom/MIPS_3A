//Gère la mémoire de données

#include "translation.h"
#include "function.h"
#include "file.h"


typedef struct cell cell;

struct cell {
  unsigned int address; /* Addresse de l'instruction */
  char data ; /* contenue de la cellule */
  cell* next ; /* adresse du successeur */
};

cell* data_memory;



int read_data(int address);

void write_data(int address, int data);
