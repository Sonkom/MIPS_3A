//Code concernant la traduction des instructions MIPS en leurs formes hexadécimales
#include "translation.h"

int translate(char* line){
  int result,inst_len,i=0,j=0,end_op;
  int op[4];

  while(*(line+i) != ' ' || *(line+i+1) != '\0') i++;
  inst_len=i;

  while(*(line+i) != '\0'){
    if(*(line+i)-'0' >= 0 && *(line+i)-'9' <= 9){
      end_op = find_char_r(line,',', i,strlen(line)-1);

      if(end_op == -1) end_op = strlen(line);
      op[j]=str_to_int(line, i, end_op-1);
      printf("%d\n",op[j] );
      j++;
      i=find_char_r(line,',', i,strlen(line)-1);
    }else
      i++;
  }

  if(!strncmp(line, "NOP",inst_len)){
    result = translate_NOP();

  }else if(!strncmp(line, "ADD", inst_len)){
    result = translate_ADD(op[0],op[1],op[2]);

  }else if(!strncmp(line, "AND", inst_len)){
    result = translate_AND(op[0],op[1],op[2]);

  }else if(!strncmp(line, "JR", inst_len)){
    result = translate_JR(op[0],op[1]);

  }else if(!strncmp(line, "MFHI", inst_len)){
    result = translate_MFHI(op[0]);

  }else if(!strncmp(line, "MFLO", inst_len)){
    result = translate_MFLO(op[0]);

  }else if(!strncmp(line, "MULT", inst_len)){
    result = translate_MULT(op[0],op[1]);

  }else if(!strncmp(line, "OR", inst_len)){
    result = translate_OR(op[0],op[1],op[2]);

  }else if(!strncmp(line, "DIV", inst_len)){
    result = translate_DIV(op[0],op[1]);

  }else if(!strncmp(line, "ROTR", inst_len)){
    result = translate_ROTR(op[0],op[1],op[2],op[3]);

  }else if(!strncmp(line, "SLL", inst_len)){
    result = translate_SLL(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLT", inst_len)){
    result = translate_SLT(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SRL", inst_len)){
    result = translate_SRL(op[0],op[1],op[2],op[3]);

  }else if(!strncmp(line, "SUB", inst_len)){
    result = translate_SUB(op[0],op[1],op[2]);

  }else if(!strncmp(line, "XOR", inst_len)){
    result = translate_XOR(op[0],op[1],op[2]);

  }else if(!strncmp(line, "ADDI", inst_len)){
    result = translate_ADDI(op[0],op[1],op[2]);

  }else if(!strncmp(line, "BEQ", inst_len)){
    result = translate_BEQ(op[0],op[1],op[2]);

  }else if(!strncmp(line, "BGTZ", inst_len)){
    result = translate_BGTZ(op[0],op[1]);

  }else if(!strncmp(line, "BLEZ", inst_len)){
    result = translate_BLEZ(op[0],op[1]);

  }else if(!strncmp(line, "BNE", inst_len)){
    result = translate_BNE(op[0],op[1],op[2]);

  }else if(!strncmp(line, "LUI", inst_len)){
    result = translate_LUI(op[0],op[1]);

  }else if(!strncmp(line, "SW", inst_len)){
    result = translate_SW(op[0],op[1],op[2]);

  }else if(!strncmp(line, "LW", inst_len)){
    result = translate_LW(op[0],op[1],op[2]);

  }else if(!strncmp(line, "J", inst_len)){
    result = translate_J(op[0]);

  }else if(!strncmp(line, "JAL", inst_len)){
    result = translate_JAL(op[0]);

  }else if(!strncmp(line, "SYSCALL", inst_len)){
    result = translate_SYSCALL(op[0]);
  }else{
    printf("ERREUR : Opération inconnu\n");
    result = -1; //Cas d'erreur, il est impossible d'avoir 0xFFFFFFF0 dans les autres cas d'où l'utilisation de -1
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
