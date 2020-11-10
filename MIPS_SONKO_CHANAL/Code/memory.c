#include "memory.h"

void init_registers(){
  for(int i=0; i<NBR_REGISTERS; i++) registers[i]=0;
}

void print_registers(){
  printf("Etat des registres :\n");
  for(int i=0; i<NBR_REGISTERS; i++){
    printf("%s : %.8x", registers_name[i], registers[i]);
    if(i%4==0) printf("\n");
  }
}
