#include "translation.h"
#include "function.h"

#define LENLINE 20


int main(int argc, char *argv[]) {

  FILE *file_source, *file_result;
  char *name_source, *name_result;
  char character, read_line[LENLINE];
  int index = 0;
  int line_hexa;

  if (argc < 3) printf("ERREUR : Arguments manquants\n");
  else {

    name_source = *(argv+1);
    name_result = *(argv+2);

    file_source = fopen(name_source, "r");
    if(file_source == NULL) {
      perror("Probleme d'ouverture fichier");
      exit(1);
    }

    file_result = fopen(name_result, "w");
    if(file_result == NULL) {
      perror("Probleme d'ouverture fichier");
      exit(1);
    }

    while (!feof(file_source)) {
      fscanf(file_source, "%c", &character);

      if(character != '\n'){
        read_line[index] = character;
        index++;
      } else {
        read_line[index] = '\0';
        index = 0;

        line_hexa = translate(read_line);
        if (line_hexa != -1)
            fprintf(file_result, "%x\n",line_hexa);
        else break;
      }
    }
  }

  fclose(file_result);
  fclose(file_source);


  return 0;
}
