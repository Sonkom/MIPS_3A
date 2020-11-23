//Gère le processeur (registre + exécution d'instruction)
#include "registers.h"

void init_registers(){
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
  printf("---- Registers state ----\n\n");
  for(int i=0; i<NBR_REGISTERS; i++){
    printf(" %s : 0x%.8x",registers_name[i], registers[i]);
    if((i%4==3 && i != 0) || i+1==NBR_REGISTERS) printf("\n");
  }
  printf("\n");
}

int read_register(int index_register){
  return registers[index_register];
}

void write_register(int index_register, int value){
  registers[index_register] = value;
}

int exec_ADD(int instruction){
  int error_code = 0;
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;

  if( read_register(rs) > MAX_SIGNED_INT - read_register(rt)){
    error_code = 0b10;
    printf("10 : ERREUR : Résultat trop grand pour un signé\n");
  }

  if(read_register(rs) < MIN_SIGNED_INT - read_register(rt)){
    error_code = 0b11;
    printf("11 : ERREUR : Résultat trop petit pour un signé\n");
  }

  if(!error_code){
    write_register(rd, read_register(rs) + read_register(rt));
    *pc += 4;
  }

  return error_code;
}

int exec_ADDI(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      imm = instruction & create_mask(0,15);
  write_register(rt , read_register(rs)+imm);
  *pc += 4;
  return 0;
}

int exec_AND(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;
  write_register(rd, read_register(rs) & read_register(rt));
  *pc += 4;
  return 0;
}


int exec_BEQ(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      offset = instruction & create_mask(0,15);
  if(read_register(rs)==read_register(rt)){
    *pc += offset << 2;
  }else{
    *pc += 4;
  }
  return 0;
}

int exec_BGTZ(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      offset = instruction & create_mask(0,15);
  if(read_register(rs)>0){
    *pc += offset << 2;
  }else{
    *pc += 4;
  }
  return 0;
}

int exec_BLEZ(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      offset = instruction & create_mask(0,15);
  if(read_register(rs)<=0){
    *pc += offset << 2;
  }else{
    *pc += 4;
  }
  return 0;
}

int exec_BNE(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      offset = instruction & create_mask(0,15);
  if(read_register(rs)!=read_register(rt)){
    *pc += offset << 2;
  }else{
    *pc += 4;
  }
  return 0;
}

int exec_DIV(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16;
  *lo=read_register(rs)/read_register(rt);
  *hi=read_register(rs)%read_register(rt);
  return 0;
}

int exec_J(int instruction){return 0;}
int exec_JAL(int instruction){return 0;}
int exec_JR(int instruction){return 0;}
int exec_LUI(int instruction){return 0;}
int exec_LW(int instruction){return 0;}
int exec_MFHI(int instruction){return 0;}
int exec_MFLO(int instruction){return 0;}
int exec_MULT(int instruction){return 0;}
int exec_NOP(int instruction){return 0;}
int exec_OR(int instruction){return 0;}
int exec_ROTR(int instruction){return 0;}
int exec_SLL(int instruction){return 0;}
int exec_SLT(int instruction){return 0;}
int exec_SRL(int instruction){return 0;}
int exec_SUB(int instruction){return 0;}
int exec_SW(int instruction){return 0;}
int exec_XOR(int instruction){return 0;}
int exec_ADDIU(int instruction){return 0;}
int exec_ADDU(int instruction){return 0;}
int exec_ANDI(int instruction){return 0;}
int exec_BGEZ(int instruction){return 0;}
int exec_BGEZAL(int instruction){return 0;}
int exec_BLTZ(int instruction){return 0;}
int exec_BLTZAL(int instruction){return 0;}
int exec_DIVU(int instruction){return 0;}
int exec_LB(int instruction){return 0;}
int exec_MULTU(int instruction){return 0;}
int exec_ORI(int instruction){return 0;}
int exec_SB(int instruction){return 0;}
int exec_SLLV(int instruction){return 0;}
int exec_SLTI(int instruction){return 0;}
int exec_SLTIU(int instruction){return 0;}
int exec_SLTU(int instruction){return 0;}
int exec_SRA(int instruction){return 0;}
int exec_SRLV(int instruction){return 0;}
int exec_SUBU(int instruction){return 0;}
int exec_XORI(int instruction){return 0;}
