//Gère la mémoire de données

#include "memory.h"

/*------ FONCTIONS DE GESTION DE LA LISTE CHAÎNÉE ------*/

void init_data_memory(void){
  data_memory = (cell *)malloc(sizeof(cell));
  data_memory->address = 0x0;
  data_memory->next = NULL;
  data_memory->data = 0x0;
}

cell* add_cell(int address, char data){
  cell * new_cell = NULL;
  if (data_counter == 0xFFFFFFFF) printf("ERROR : The memory's capacity has reached its limits\n");
  else {
    new_cell = (cell *)malloc(sizeof(cell));
    new_cell->address = address;
    new_cell->data = data;
    data_counter++;
  }
  return new_cell;
}

void print_memory(void){
  cell* memory_printer = data_memory;
  unsigned int index = 0;

  printf("---- Memory State ----\n\n");
  while(memory_printer != NULL) {
    printf("      @%.8x : %.2x",memory_printer->address, memory_printer->data);
    index++;
    if (index == 0%4) printf("\n");
    memory_printer = memory_printer->next;
  }
  printf("\n");
  printf("\nData quantity used : %d bytes\n",data_counter);
}

void free_memory(void){
  cell *buffer1 = data_memory, *buffer2 = NULL;

  while (buffer1 != NULL){
    buffer2 = buffer1;
    buffer1 = buffer1->next;
    free(buffer2);
  }
}

/*------ FONCTIONS POUR LA MÉMOIRE DE DONNÉES ------*/

int read_data(unsigned int address){
  cell *search_address = data_memory;
  int data = 0;

  // Recherche de la cellule mémoire où contient la donnée
  while ((search_address != NULL) && (search_address->address < address)) {
    search_address = search_address->next;
  }

  // Lecture de la donnée
  if (search_address->address == address)
    for (int index = 0; (index < 4) && (search_address->address == address+index); index++){
      if (index != 0) data = data << 8;
      data += search_address->data;
      search_address = search_address->next;
    }

  return data;
}

char write_data(unsigned int address, int data) {
  cell *search_address = data_memory, *writer = data_memory, *buffer = NULL;
  char data_bytes[4];
  char overflow_check = 1;

  /* Recherche de la cellule d'adresse donnée */
  while ((search_address != NULL) && (address <= search_address->address)) {
    writer = search_address;
    search_address = search_address->next;
  }

  /* Séparation de la valeur de la valeur data sur 4 octets en 4 valeurs d'un octet */
  data_bytes[0] = (data >> 24) & 0xFF;
  data_bytes[1] = (data >> 16) & 0xFF;
  data_bytes[2] = (data >> 8) & 0xFF;
  data_bytes[3] = data & 0xFF;

  /* Ecriture en mémoire */
  if (writer != NULL) buffer = writer->next;

  for (unsigned int index = 0; (index < 4) && overflow_check; index++){
    if (writer == NULL) {
      writer = add_cell(address+index, data_bytes[index]);
      if (writer != NULL) writer = writer->next;
      else overflow_check = 0;
    } else if (writer->address == address+index) {
      writer->data = data_bytes[index];
      writer = writer->next;
    } else {
      writer->next = add_cell(address+index, data_bytes[index]);
      if (writer->next != NULL) {
        writer->next->next = buffer;
        writer = buffer;
      }
      else overflow_check = 0;
    }
    if (buffer != NULL) buffer = buffer->next;
  }
  return overflow_check;
}
