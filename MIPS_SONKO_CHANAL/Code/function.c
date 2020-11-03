//Code concernant les fonctions utiles supplémentaires
#include "function.h"

//Convertie la chaine de caractère str[d:f] en un entier
int str_to_int(char* str, int d, int f){
  int power = 1, success = 1, result = 0, sign = 1;
  if(f<d){
    printf("ERREUR : Indice incohérent\n");
  }else{

    if(f>strlen(str)) f=strlen(str)-1;

    if(*(str+d) == '-'){
      d++;
      sign=-1;
    }

    for(int i=f; i>=d && success!=-1; i--){
      result += power * ( (*(str+i)) - '0');
      power *= 10;
      if(*(str+i)-'0' < 0 || *(str+i)-'9' > 9){
        printf("ERREUR : Impossible de convertir en entier : Caractère \n");
        success = -1;
      }
    }

    if(success != -1) result *= sign;
  }

  return result;
}

int find_char_r(char* str, char c, int d, int f){
  int position=-1, i=d;
  while(position == -1 && str[i] != '\0' && i<=f){
    if(str[i] == c) position = i;
    i++;
  }
  return position;
}
