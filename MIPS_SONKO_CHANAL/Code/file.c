// Gère la lecture du programme dans un fichier en entrée, et l'écriture du code hexadécimal dans un fichier en sortie

#include "file.h"

 /* ------ UTILITAIRE À LA LISTE CHAINÉE ------*/

program init_program(void){
   program init = (program)malloc(sizeof(instruction));
   init->next = NULL;
   init->address = 0;
   return init;
 }

instruction* add_instruct(program prog) {

  program last = prog;
  instruction* instruct = (instruction *)malloc(sizeof(instruction));
  instruct->next = NULL;

  while (last->next != NULL) last = last->next;
  last->next = instruct;

  return instruct;
}

void free_prog(program prog){
  program buffer1 = prog, buffer2 = NULL;

  while (buffer1 != NULL){
    buffer2 = buffer1;
    buffer1 = buffer1->next;
    free(buffer2);
  }
}

void print_prog(program prog) {
  program prog_printer = prog->next;

  printf("*** Prrogram loaded - Ready to be executed ***\n\n");
  while(prog_printer != NULL) {
    printf("      %.8x %.8x : { %s }\n",prog_printer->address, prog_printer->line_hexa ,prog_printer->line);
    prog_printer = prog_printer->next;
  }
  printf("\n\n");
}

/* ------ LECTURE + ÉCRITURE DE FICHIER ------ */

void read_file(char* name_source, program prog){
  FILE *file_source;
  char character, *read_line = NULL;
  int index = 0, is_comment = 0;
  unsigned int instruct_address = 0;
  instruction* instruct = NULL;

  file_source = fopen(name_source, "r");
  if(file_source == NULL) {
    perror("Probleme d'ouverture fichier");
    exit(1);
  }

  while (!feof(file_source)) {

    fscanf(file_source, "%c", &character);

    if(character != '\n' && character != '\r'){

      if (character == '#') is_comment = 1;
      if (!is_comment && (!((index == 0) && (character == ' '))))
        {
          if (instruct == NULL){
            instruct = add_instruct(prog);
            read_line = instruct->line;
            instruct->address = instruct_address;
            instruct_address+=4;
          }
          read_line[index] = character;
          index++;
        }

    } else {
      if (read_line != NULL) read_line[index] = '\0';
      is_comment = 0;


      if (index != 0) {
        index = 0;
        instruct = NULL;
        read_line = NULL;
      }
    }
  }
  fclose(file_source);
}

void translate_to_hexa(program prog){
  instruction* translater = prog->next;

  while(translater != NULL) {
    translater->line_hexa = translate(translater->line);
    translater = translater->next;
  }
}

void write_file(char* name_result, program prog){
  instruction* file_writer = prog->next;
  FILE *file_result;
  int success = 1;

  file_result = fopen(name_result, "w");
  if(file_result == NULL) {
    perror("Probleme d'ouverture fichier");
    exit(1);
  }

  while ((file_writer != NULL) && success){
    if (file_writer->line_hexa != -1) fprintf(file_result, "%.8x\n",file_writer->line_hexa);
    else success = 0;
    file_writer = file_writer->next;
  }
  fclose(file_result);
}
