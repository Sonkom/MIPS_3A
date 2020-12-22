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
  if (data_counter >= 0x100000000) printf("ERROR : The memory's capacity has reached its limits\n");
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
    if(memory_printer->address%4 == 0) printf("  @%.8x : |",memory_printer->address);
    printf(" %.2x |", memory_printer->data);
    index++;
    if (index%12 == 0) printf("\n");
    memory_printer = memory_printer->next;
  }
  printf("\n");
  printf("\nData quantity used : %ld bytes\n",data_counter);
}

void free_memory(void){
  cell *buffer = data_memory, *delete = NULL;

  while (buffer != NULL){
    delete = buffer;
    buffer = buffer->next;
    free(delete);
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
  cell *search_address = data_memory, *writer = data_memory, *next_buffer = NULL, *prev_buffer = NULL;
  char data_bytes[4];
  char overflow_check = 1;

  /* Recherche de la cellule d'adresse donnée */
  while ((search_address != NULL) && (address >= search_address->address)) {
    prev_buffer = writer;
    writer = search_address;
    search_address = search_address->next;
  }

  /* Séparation de la valeur de la valeur data sur 4 octets en 4 valeurs d'un octet */
  data_bytes[0] = (data >> 24) & 0xFF;
  data_bytes[1] = (data >> 16) & 0xFF;
  data_bytes[2] = (data >> 8) & 0xFF;
  data_bytes[3] = data & 0xFF;

  /* Ecriture en mémoire */
  if (writer != NULL) next_buffer = writer->next;

  for (int index = 0; (index < 4) && overflow_check; index++){
    if ((writer != NULL) && (writer->address == address + index)) {
      writer->data = data_bytes[index];
      prev_buffer = writer;
      writer = writer->next;
      if (next_buffer != NULL) next_buffer = next_buffer->next;
    } else if ((writer != NULL) && (writer->address > address + index)){
      next_buffer = writer;
      writer = add_cell(address+index, data_bytes[index]);
      if(writer != NULL) prev_buffer->next = writer;
      else overflow_check = 0;
    } else {
      if (writer != NULL) prev_buffer = writer;
      writer = add_cell(address+index, data_bytes[index]);
      if(writer != NULL) prev_buffer->next = writer;
      else overflow_check = 0;
    }
  }
  writer->next = next_buffer;

  return overflow_check;
}
