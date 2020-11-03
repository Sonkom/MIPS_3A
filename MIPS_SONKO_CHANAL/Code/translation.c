//Code concernant la traduction des instructions MIPS en leurs formes hexadécimales
#include "translation.h"

int translate(char* line){
  int result,inst_len,i=0,j=0;
  int op[4];
  while(*(line+i) != ' ') i++;
  inst_len=i;

  while(*(line+i) != '\0'){

  }

  if(!strncmp(line, "NOP",inst_len)){
    result = translate_NOP();
  }else if(!strncmp(line, "ADD", inst_len)){

    //result = translate_ADD()
  }





  return result;
}


int translate_immediat(int code, int r0, int r1, int imm){
  return (code << 26) + (r0 << 21) + (r1 << 16) + imm;
}

int translate_direct(int special, int r0, int r1, int r2, int r3, int code){
  return (special << 26) + (r0 << 21) + (r1 << 16) + (r2 << 11) + (r3 << 6)  + code;
}

int translate_jump(int code, int adress){
  return (code << 26) + adress;
}

/*--------- DIRECT ---------*/
int translate_ADD(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,rd,0,0b100000);
}

int translate_AND(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,rd,0,0b100100);
}

int translate_JR(int rs, int hint){
  return translate_direct(0,rs,0,0,hint,0b001000);
}

int translate_MFHI(int rd){
  return translate_direct(0,0,0,rd,0,0b010000);
}

int translate_MFLO(int rd){
  return translate_direct(0,0,0,rd,0,0b010010);
}

int translate_MULT(int rs, int rt){
  return translate_direct(0,rs,rt,0,0,0b011000);
}

int translate_NOP(){
  return translate_direct(0,0,0,0,0,0);
}

int translate_OR(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,0,0,0b100101);
}

int translate_DIV(int rs, int rt){
  return translate_direct(0,rs,rt,0,0,0b011010);
}

int translate_ROTR(int ri, int rt, int rd, int sa){
  return translate_direct(0,ri,rt,rd,sa,0b000010);
}

int translate_SLL(int rt, int rd, int sa){
  return translate_direct(0,0,rt,rd,sa,0b000000);
}

int translate_SLT(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,rd,0,0b101010);
}

int translate_SRL(int r0, int rt, int rd, int sa){
  return translate_direct(0,r0,rt,rd,sa,0b000010);
}

int translate_SUB(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,rd,0,0b100010);
}

int translate_XOR(int rs, int rt, int rd){
  return translate_direct(0,rs,rt,rd,0,0b100110);
}

/*--------- IMMÉDIAT ---------*/
int translate_ADDI(int rs, int rt, int imm){
  return translate_immediat(0b001000, rs, rt, imm);
}

int translate_BEQ(int rs, int rt, int offset){
  return translate_immediat(0b000100, rs, rt, offset);
}

int translate_BGTZ(int rs, int offset){
  return translate_immediat(0b000111, rs, 0, offset);
}

int translate_BLEZ(int rs, int offset){
  return translate_immediat(0b000110, rs, 0, offset);
}

int translate_BNE(int rs, int rt, int offset){
  return translate_immediat(0b000101, rs, rt, offset);
}

int translate_LUI(int rt, int imm){
  return translate_immediat(0b001111, 0, rt, imm);
}

int translate_SW(int base, int rt, int offset){
  return translate_immediat(0b101011, base, rt, offset);
}

int translate_LW(int base, int rt, int offset){
  return translate_immediat(0b100011, base, rt, offset);
}

/*--------- JUMP ---------*/
int translate_J(int instr_index){
  return translate_jump(0b000010, instr_index);
}

int translate_JAL(int instr_index){
  return translate_jump(0b000011, instr_index);
}

/*--------- ? ---------*/
int translate_SYSCALL(int code){
  return (code << 6) + 0b001100;
}
