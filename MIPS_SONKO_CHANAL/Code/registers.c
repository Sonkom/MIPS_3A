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
    printf(" %s : %-11d",registers_name[i], registers[i]);
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

  /* ===== Tests Erreurs ==== */

  if(read_register(rt) > 0 && read_register(rs) > MAX_SIGNED_INT - read_register(rt)) error_code = 0b10; // Overflow

  if(read_register(rt) < 0 && read_register(rs) <  MIN_SIGNED_INT - read_register(rt)) error_code = 0b11; // Underflow

  /* ======================= */

  if(!error_code){
    write_register(rd, read_register(rs) + read_register(rt));
    *pc += 4;
  }

  return error_code;
}

int exec_ADDI(int instruction){
  int error_code = 0;
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      imm = instruction & create_mask(0,15);

  if(imm & create_mask(15,15)) imm = imm | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

  /* ===== Tests Erreurs ==== */

  if(read_register(rt) > 0 && read_register(rs) > MAX_SIGNED_INT - imm) error_code = 0b10; // Overflow

  if(read_register(rt) < 0 && read_register(rs) < MIN_SIGNED_INT - imm) error_code = 0b11; // Underflow

  /* ======================= */

  if(!error_code){
    write_register(rt , read_register(rs)+imm);
    *pc += 4;
  }

  return error_code;
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

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

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

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

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

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

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

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

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

  if(read_register(rt) != 0) *lo=read_register(rs)/read_register(rt);
  *hi=read_register(rs)%read_register(rt);
  *pc += 4;

  return 0;
}


int exec_J(int instruction){
  int line = (instruction & create_mask(0,25));

  *pc = line;
  return 0;
}

int exec_JAL(int instruction){
  int line = (instruction & create_mask(0,25));

  registers[31] = *pc + 8;
  *pc = line;
  return 0;
}


int exec_JR(int instruction){
  int rs = (instruction & create_mask(21,25))>>21;

  *pc=read_register(rs);

  return 0;
}

int exec_LUI(int instruction){
  int rt = (instruction & create_mask(16,20))>>16,
      imm = instruction & create_mask(0,15);

  write_register(rt, (imm << 16) & create_mask(16,31));
  *pc+=4;

  return 0;
}

int exec_LW(int instruction){
  int base = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      offset = instruction & create_mask(0,15);

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

  write_register(rt,read_data(read_register(base) + offset));
  *pc+=4;

  return 0;
}

int exec_MFHI(int instruction){
  int rd = (instruction & create_mask(11,15))>>11;

  write_register(rd,*hi);
  *pc+=4;

  return 0;
}

int exec_MFLO(int instruction){
  int rd = (instruction & create_mask(11,15))>>11;

  write_register(rd,*lo);
  *pc+=4;

  return 0;
}

int exec_MULT(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16;

  long res_64 = (long)read_register(rs)*(long)read_register(rt);

  *lo=res_64 & create_mask(0,31);
  *hi=res_64 >> 32;
  *pc+=4;

  return 0;
}

int exec_NOP(int instruction){
  *pc+=4;
  return 0;
}

int exec_OR(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;

  write_register(rd, read_register(rs) | read_register(rt));
  *pc += 4;

  return 0;
}

int exec_ROTR(int instruction){
  int rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11,
      sa = (instruction & create_mask(6,10))>>6;

  int rt_value = read_register(rt);

  for(int i=0; i<sa; i++){
    if((rt_value & create_mask(31,31)) == create_mask(31,31)) rt_value = (rt_value << 1) + 1;
    else rt_value = rt_value << 1;
  }

  write_register(rd, rt_value);
  *pc+=4;

  return 0;
}

int exec_SLL(int instruction){
  int rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11,
      sa = (instruction & create_mask(6,10))>>6;

  write_register(rd, read_register(rt) << sa);
  *pc+=4;

  return 0;
}

int exec_SLT(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;

  write_register(rd, read_register(rs) < read_register(rt));
  *pc+=4;

  return 0;
}

int exec_SRL(int instruction){
  int rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11,
      sa = (instruction & create_mask(6,10))>>6;

  write_register(rd, read_register(rt) >> sa);
  *pc+=4;

  return 0;
}

int exec_SUB(int instruction){
  int error_code = 0;
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;
      //printf("%d - %d\n", read_register(rs) , read_register(rt));

  /* ===== Tests Erreurs ==== */

  if(read_register(rs) > 0 && read_register(rs) > MAX_SIGNED_INT + read_register(rt)) error_code = 0b10; // Overflow

  if(read_register(rs) < 0 && read_register(rs) <  MIN_SIGNED_INT + read_register(rt)) error_code = 0b11; // Underflow

  /* ======================= */

  if(!error_code){
    write_register(rd, read_register(rs) - read_register(rt));
    *pc += 4;
  }

  return error_code;
}


int exec_SW(int instruction){
  int error_code = 0;
  int base = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      offset = instruction & create_mask(0,15);

  if(offset & create_mask(15,15)) offset = offset | create_mask(16,31); // Valeur négative sur 16 bits transformée en valeur négative sur 32 bits

  /* ===== Tests Erreurs ==== */

  if(offset%4 != 0) error_code = 0b100;

  /* ======================= */

  if(!error_code){
    write_data(read_register(base) + offset,read_register(rt));
    *pc+=4;
  }

  return error_code;
}

int exec_XOR(int instruction){
  int rs = (instruction & create_mask(21,25))>>21,
      rt = (instruction & create_mask(16,20))>>16,
      rd = (instruction & create_mask(11,15))>>11;

  write_register(rd, read_register(rs) ^ read_register(rt));
  *pc += 4;

  return 0;
}


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
