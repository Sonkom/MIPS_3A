//Code concernant les fonctions utiles supplémentaires
#include "function.h"

int decode_reg(char* reg){
  int reg_code = -1;
  if(!strcmp(reg,"$zero")){
    reg_code = 0;
  }else if(!strcmp(reg,"$at")){
    reg_code = 1;
  }else if(!strncmp(reg,"$v",2)){
    reg_code = *(reg+2)-'0' + 2;
  }else if(!strncmp(reg,"$a",2)){
    reg_code = *(reg+2)-'0' + 4;
  }else if(!strncmp(reg,"$t",2) && strcmp(reg,"$t8") && strcmp(reg,"$t9")){
    reg_code = *(reg+2)-'0' + 8;
  }else if(!strncmp(reg,"$s",2)){
    reg_code = *(reg+2)-'0' + 16;
  }else if(!strncmp(reg,"$t",2)){
    reg_code = *(reg+2)-'0' + 16;
  }else if(!strncmp(reg,"$k",2)){
    reg_code = *(reg+2)-'0' + 26;
  }else if(!strcmp(reg,"$gp")){
    reg_code = 28;
  }else if(!strcmp(reg,"$sp")){
    reg_code = 29;
  }else if(!strcmp(reg,"$fp")){
    reg_code = 30;
  }else if(!strcmp(reg,"$ra")){
    reg_code = 31;
  }else{
    printf("ERREUR : Registre inconnu\n");
  }
  return reg_code;
}
