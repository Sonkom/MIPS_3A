//Code concernant la traduction des instructions MIPS en leurs formes hexadécimales

#include "translation.h"

int translate(char* line){
  int result,inst_len,i=0,j=0,end_op;
  int op[3];

  while(*(line+i) != ' ' && *(line+i+1) != '\0') i++;
  inst_len=i;

  while(*(line+i) != '\0'){
    if((*(line+i)-'0' >= 0 && *(line+i)-'9' <= 9) || *(line+i) == '-'){

      end_op = find_char_r(line,',', i,strlen(line)-1);
      if(end_op == -1){
        end_op = find_char_r(line,'(', i,strlen(line)-1);
        if(end_op == -1){
          end_op = find_char_r(line,')', i,strlen(line)-1);
          if(end_op == -1) end_op = strlen(line);
        }
      }

      op[j]=str_to_int(line, i, end_op-1);
      j++;
      i=end_op;
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
    result = translate_JR(op[0],0);

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
    result = translate_ROTR(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLL", inst_len)){
    result = translate_SLL(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLT", inst_len)){
    result = translate_SLT(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SRL", inst_len)){
    result = translate_SRL(op[0],op[1],op[2]);

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

  }else if(!strncmp(line, "ADDIU", inst_len)){
    result = translate_ADDIU(op[0],op[1],op[2]);

  }else if(!strncmp(line, "ADDU", inst_len)){
    result = translate_ADDU(op[0],op[1],op[2]);

  }else if(!strncmp(line, "ANDI", inst_len)){
    result = translate_ANDI(op[0],op[1],op[2]);

  }else if(!strncmp(line, "BGEZ", inst_len)){
    result = translate_BGEZ(op[0],op[1]);

  }else if(!strncmp(line, "BGEZAL", inst_len)){
    result = translate_BGEZAL(op[0],op[1]);

  }else if(!strncmp(line, "BLTZ", inst_len)){
    result = translate_BLTZ(op[0],op[1]);

  }else if(!strncmp(line, "BLTZAL", inst_len)){
    result = translate_BLTZAL(op[0],op[1]);

  }else if(!strncmp(line, "DIVU", inst_len)){
    result = translate_DIVU(op[0],op[1]);

  }else if(!strncmp(line, "LB", inst_len)){
    result = translate_LB(op[0],op[1],op[2]);

  }else if(!strncmp(line, "MULTU", inst_len)){
    result = translate_MULTU(op[0],op[1]);

  }else if(!strncmp(line, "ORI", inst_len)){
    result = translate_ORI(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SB", inst_len)){
    result = translate_SB(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLLV", inst_len)){
    result = translate_SLLV(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLTI", inst_len)){
    result = translate_SLTI(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLTIU", inst_len)){
    result = translate_SLTIU(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SLTU", inst_len)){
    result = translate_SLTU(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SRA", inst_len)){
    result = translate_SRA(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SRLV", inst_len)){
    result = translate_SRLV(op[0],op[1],op[2]);

  }else if(!strncmp(line, "SUBU", inst_len)){
    result = translate_SUBU(op[0],op[1],op[2]);

  }else if(!strncmp(line, "XORI", inst_len)){
    result = translate_XORI(op[0],op[1],op[2]);

  }else{
    printf("ERREUR : Opération inconnu\n");
    result = -1; //Cas d'erreur, il est impossible d'avoir 0xFFFFFFF0 dans les autres cas d'où l'utilisation de -1
  }

  return result;
}


int translate_immediat(int code, int r0, int r1, int imm){
  return (code << 26) + (r0 << 21) + (r1 << 16) + (imm & 0x0000FFFF);
}

int translate_direct(int special, int r0, int r1, int r2, int r3, int code){
  return (special << 26) + (r0 << 21) + (r1 << 16) + (r2 << 11) + (r3 << 6)  + code;
}

int translate_jump(int code, int adress){
  return (code << 26) + adress;
}

/*--------- DIRECT ---------*/
int translate_ADD(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b100000);
}

int translate_AND(int rd, int rs, int rt){
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

int translate_OR(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b100101);
}

int translate_DIV(int rs, int rt){
  return translate_direct(0,rs,rt,0,0,0b011010);
}

int translate_ROTR(int rd, int rt, int sa){
  return translate_direct(0,1,rt,rd,sa,0b000010);
}

int translate_SLL(int rd, int rt, int sa){
  return translate_direct(0,0,rt,rd,sa,0b000000);
}

int translate_SLT(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b101010);
}

int translate_SRL(int rd, int rt, int sa){
  return translate_direct(0,0,rt,rd,sa,0b000010);
}

int translate_SUB(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b100010);
}

int translate_XOR(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b100110);
}

/*--------- IMMÉDIAT ---------*/
int translate_ADDI(int rt, int rs, int imm){
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

int translate_SW(int rt, int offset, int base){
  return translate_immediat(0b101011, base, rt, offset);
}

int translate_LW(int rt, int offset, int base){
  return translate_immediat(0b100011, base, rt, offset);
}

/*--------- JUMP ---------*/
int translate_J(int instr_index){
  return translate_jump(0b000010, instr_index);
}

int translate_JAL(int instr_index){
  return translate_jump(0b000011, instr_index);
}

/*--------- OPT ---------*/
int translate_ADDIU(int rt, int rs, int imm){
  return translate_immediat(0b001001,rs,rt,imm);
}

int translate_ADDU(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rt,0,0b100001);
}

int translate_ANDI(int rt, int rs, int imm){
  return translate_immediat(0b001100,rs,rt,imm);
}

int translate_BGEZ(int rs, int offset){
  return translate_immediat(0b000001,rs,1,offset);
}

int translate_BGEZAL(int rs, int offset){
  return translate_immediat(0b000001,rs,0b10001,offset);
}

int translate_BLTZ(int rs, int offset){
  return translate_immediat(0b000001,rs,0,offset);
}

int translate_BLTZAL(int rs, int offset){
  return translate_immediat(0b000001,rs,0b10000,offset);
}

int translate_DIVU(int rs, int rt){
  return translate_direct(0,rs,rt,0,0,0b011011);
}

int translate_LB(int rt, int offset, int rs){
  return translate_immediat(0b100000,rs,rt,offset);
}

int translate_MULTU(int rs, int rt){
  return translate_direct(0,rs,rt,0,0,0b011001);
}

int translate_ORI(int rt, int rs, int imm){
  return translate_immediat(0b001101,rs,rt,imm);
}

int translate_SB(int rt, int offset, int rs){
  return translate_immediat(0b101000,rs,rt,offset);
}

int translate_SLLV(int rd, int rt, int rs){
  return translate_direct(0,rs,rt,rd,0,0b000100);
}

int translate_SLTI(int rt, int rs,int imm){
  return translate_immediat(0b001010,rs,rt,imm);
}

int translate_SLTIU(int rt, int rs,int imm){
  return translate_immediat(0b001011,rs,rt,imm);
}

int translate_SLTU(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b101011);
}

int translate_SRA(int rd, int rt, int sa){
  return translate_direct(0,0,rt,rd,sa,0b000011);
}

int translate_SRLV(int rd, int rt, int rs){
  return translate_direct(0,rs,rt,rd,0,0b000110);
}

int translate_SUBU(int rd, int rs, int rt){
  return translate_direct(0,rs,rt,rd,0,0b100011);
}

int translate_XORI(int rt, int rs, int imm){
  return translate_immediat(0b001110,rs,rt,imm);
}
