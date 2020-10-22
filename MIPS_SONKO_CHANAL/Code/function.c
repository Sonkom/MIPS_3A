//Code concernant les fonctions utiles supplémentaires
#include "function.h"
/*
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
}*/

//Convertie la chaine de caractère str[d:f] en un entier
int str_to_int(char* str, int d, int f){
  int power=1, result=-1, sign=1;
  if(f<d){
    printf("ERREUR : Indice incohérent\n");
  }else{
    result = 1;

    if(f>strlen(str)) f=strlen(str);

    if(*str+d == '-'){
      d++;
      sign=-1;
    }

    for(int i=f; i>=d && result!=-1; i--){
      printf("result : %d\n", result);
      result += power * ( (*(str+i)) - '0');
      power *= 10;
      if(*(str+i)-'0' < 0 || *(str+i)-'9' > 9){
        printf("ERREUR : Impossible de convertir en entier : Caractère \n");
        result = -1;
      }
    }

    if(result != -1) result *= sign;
  }

  return result;
}
