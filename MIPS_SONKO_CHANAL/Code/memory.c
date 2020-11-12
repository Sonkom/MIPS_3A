//Gère la mémoire de données

#include "memory.h"

void init_data_memory(void){
  data_memory = (cell *)malloc(sizeof(cell));
  data_memory->address = 0x0;
  data_memory->next = NULL;
  data_memory->data = 0x0;
}

cell* add_cell(int address, char data){
  cell *new_cell = (cell *)malloc(sizeof(cell));
  new_cell->address = address;
  new_cell->data = data;
  return new_cell;
}

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

void write_data(unsigned int address, int data) {
  cell *search_address = data_memory, *writer = data_memory, *buffer = NULL;
  char data_bytes[4];

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

  for (unsigned int index = 0; index < 4; index++){
    if (writer == NULL) {
      writer = add_cell(address+index, data_bytes[index]);
      writer = writer->next;
    } else if (writer->address == address+index) {
      writer->data = data_bytes[index];
      writer = writer->next;
    } else {
      writer->next = add_cell(address+index, data_bytes[index]);
      writer->next->next = buffer;
      writer = buffer;
    }
    if (buffer != NULL) buffer = buffer->next;
  }
}

/*
void write_data_char(cell* write, unsigned int address, char* data_bytes){
  cell *buffer = write, *buffer_next = write->next;

  for (unsigned int index = 0; index < 4; index++){
    if (buffer == NULL) {
      buffer = add_cell(address+index, data_bytes[index]);
      buffer = buffer->next;
    } else if (buffer->address == address+index) {
      buffer->data = data_bytes[index];
      buffer = buffer->next;
    } else {
      buffer->next = add_cell(address+index, data_bytes[index]);
      buffer->next->next = buffer_next;
      buffer = buffer_next;
    }
    if (buffer_next != NULL) buffer_next = buffer_next->next;
  }
}*/
