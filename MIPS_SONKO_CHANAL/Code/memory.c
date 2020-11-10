#include "memory.h"

void init_registers(){
  for(int i=0; i<NBR_REGISTERS; i++) registers[i]=0;
}

void print_registers(){
  /*char* registers_name[NBR_REGISTERS];
  registers_name[0] = "zero";
  registers_name[1], "at";
  registers_name[2], "v0";
  registers_name[3], "v1";
  registers_name[4], "a0";
  registers_name[5], "a1";
  registers_name[6], "a2";
  registers_name[7], "a3";
  registers_name[8], "t0";
  registers_name[9], "t1";
  registers_name[10], "t2";
  registers_name[11], "t3";
  registers_name[12], "t4";
  registers_name[13], "t5";
  registers_name[14], "t6";
  registers_name[15], "t7";
  registers_name[16], "s0";
  registers_name[17], "s1";
  registers_name[18], "s2";
  registers_name[19], "s3";
  registers_name[20], "s4";
  registers_name[21], "s5";
  registers_name[22], "s6";
  registers_name[23], "s7";
  registers_name[24], "t8";
  registers_name[25], "t9";
  registers_name[26], "k0";
  registers_name[27], "k1";
  registers_name[28], "gp";
  registers_name[29], "sp";
  registers_name[30], "fp";
  registers_name[31], "ra";
  registers_name[32], "hi";
  registers_name[33], "lo";
  registers_name[34], "pc";*/
  printf("Etat des registres :\n");
  for(int i=0; i<NBR_REGISTERS; i++){
    printf("%s : %.8x","ma bite" /*registers_name[i]*/, registers[i]);
    if(i%4==0) printf("\n");
  }
}
