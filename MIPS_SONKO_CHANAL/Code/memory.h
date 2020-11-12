//Gère la mémoire de données

#include "translation.h"
#include "function.h"
#include "registers.h"


typedef struct cell cell;

struct cell {
  unsigned int address; /* Addresse de l'instruction */
  char data ; /* contenue de la cellule */
  cell* next ; /* adresse du successeur */
};

cell* data_memory;

void init_data_memory(void);

cell* add_cell(int address, char data);

void write_data(unsigned int address, int data);

int read_data(unsigned int address);

//void write_data_char(cell* write, unsigned int address, char* data_bytes);
