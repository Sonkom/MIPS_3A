//Gère le processeur (registre + exécution d'instruction)
#include "file.h"
#include "registers.h"
#include "function.h"

void init_registers(){
   gp = registers+28; /* Global Pointer */
   sp = registers+29; /* Stack Pointer */
   fp = registers+30; /* Frame Pointer */
   ra = registers+31; /* Return Adress */
  // Registres de stockage pour des opérations entre deux données de 32 bits;
   hi = registers+32;
   lo = registers+33;

   pc = registers+34; /* PROGRAM COUNTER */

   /* Creation du tableau du nom des registres */
   registers_name[0] = "zero";
   registers_name[1] = "  at";
   registers_name[2] = "  v0";
   registers_name[3] = "  v1";
   registers_name[4] = "  a0";
   registers_name[5] = "  a1";
   registers_name[6] = "  a2";
   registers_name[7] = "  a3";
   registers_name[8] = "  t0";
   registers_name[9] = "  t1";
   registers_name[10] = "  t2";
   registers_name[11] = "  t3";
   registers_name[12] = "  t4";
   registers_name[13] = "  t5";
   registers_name[14] = "  t6";
   registers_name[15] = "  t7";
   registers_name[16] = "  s0";
   registers_name[17] = "  s1";
   registers_name[18] = "  s2";
   registers_name[19] = "  s3";
   registers_name[20] = "  s4";
   registers_name[21] = "  s5";
   registers_name[22] = "  s6";
   registers_name[23] = "  s7";
   registers_name[24] = "  t8";
   registers_name[25] = "  t9";
   registers_name[26] = "  k0";
   registers_name[27] = "  k1";
   registers_name[28] = "  gp";
   registers_name[29] = "  sp";
   registers_name[30] = "  fp";
   registers_name[31] = "  ra";
   registers_name[32] = "  hi";
   registers_name[33] = "  lo";
   registers_name[34] = "  pc";

  for(int i=0; i<NBR_REGISTERS; i++) registers[i]=0; //Initialisation de la valeur des registres à 0
}

void print_registers(){
  printf("Etat des registres :\n");
  for(int i=0; i<NBR_REGISTERS; i++){
    printf(" %s : 0x%.8x",registers_name[i], registers[i]);
    if((i%4==3 && i != 0) || i+1==NBR_REGISTERS) printf("\n");
  }
}

int read_register(int index_register){
  return registers[index_register];
}

void write_register(int index_register, int value){
  registers[index_register] = value;
}

void execution(program prog){
  
}

void exec_ADD(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;
  write_register(rd, read_register(rs) + read_register(rt));
  *pc += 4;
}

void exec_ADDI(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      imm = instruction & create_mask(0,15);
  write_register(rt , read_register(rs)+imm);
  *pc += 4;
}

void exec_AND(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;
  write_register(rd, read_register(rs) & read_register(rt));
  *pc += 4;
}


void exec_BEQ(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      offset = instruction & create_mask(0,15);
  if(read_register(rs)==read_register(rt)){
    *pc += offset << 2;
  }else{
    *pc += 4;
  }
}
