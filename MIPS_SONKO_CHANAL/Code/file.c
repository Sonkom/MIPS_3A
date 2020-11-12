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

void execution_pointer_setup(program prog){
  instruction* setup_pointer = prog->next;

  while(setup_pointer != NULL) {
    instruct_execute_pointer(setup_pointer->line, &(setup_pointer->exec));
    setup_pointer = setup_pointer->next;
  }
}

void instruct_execute_pointer(char *line, void (**exec)(int)){
  int inst_len,i=0;

  while(*(line+i) != ' ' && *(line+i+1) != '\0') i++;
  inst_len=i;


  /*if(!strncmp(line, "NOP",inst_len)){
    exec = exec_NOP;

  }else*/ if(!strncmp(line, "ADD", inst_len)){
    *exec = &exec_ADD;

  /*}else if(!strncmp(line, "AND", inst_len)){
    exec = exec_AND;

  }else if(!strncmp(line, "JR", inst_len)){
    exec = exec_JR;

  }else if(!strncmp(line, "MFHI", inst_len)){
    exec = exec_MFHI;

  }else if(!strncmp(line, "MFLO", inst_len)){
    exec = exec_MFLO;

  }else if(!strncmp(line, "MULT", inst_len)){
    exec = exec_MULT;

  }else if(!strncmp(line, "OR", inst_len)){
    exec = exec_OR;

  }else if(!strncmp(line, "DIV", inst_len)){
    exec = exec_DIV;

  }else if(!strncmp(line, "ROTR", inst_len)){
    exec = exec_ROTR;

  }else if(!strncmp(line, "SLL", inst_len)){
    exec = exec_SLL;

  }else if(!strncmp(line, "SLT", inst_len)){
    exec = exec_SLT;

  }else if(!strncmp(line, "SRL", inst_len)){
    exec = exec_SRL;

  }else if(!strncmp(line, "SUB", inst_len)){
    exec = exec_SUB;

  }else if(!strncmp(line, "XOR", inst_len)){
    exec = exec_XOR;

  */}else if(!strncmp(line, "ADDI", inst_len)){
    *exec = &exec_ADDI;

  }else if(!strncmp(line, "BEQ", inst_len)){
    *exec = &exec_BEQ;

  /*}else if(!strncmp(line, "BGTZ", inst_len)){
    exec = exec_BGTZ;

  }else if(!strncmp(line, "BLEZ", inst_len)){
    exec = exec_BLEZ;

  }else if(!strncmp(line, "BNE", inst_len)){
    exec = exec_BNE;

  }else if(!strncmp(line, "LUI", inst_len)){
    exec = exec_LUI;

  }else if(!strncmp(line, "SW", inst_len)){
    exec = exec_SW;

  }else if(!strncmp(line, "LW", inst_len)){
    exec = exec_LW;

  }else if(!strncmp(line, "J", inst_len)){
    exec = exec_J;

  }else if(!strncmp(line, "JAL", inst_len)){
    exec = exec_JAL;

  }else if(!strncmp(line, "ADDIU", inst_len)){
    exec = exec_ADDIU;

  }else if(!strncmp(line, "ADDU", inst_len)){
    exec = exec_ADDU;

  }else if(!strncmp(line, "ANDI", inst_len)){
    exec = exec_ANDI;

  }else if(!strncmp(line, "BGEZ", inst_len)){
    exec = exec_BGEZ;

  }else if(!strncmp(line, "BGEZAL", inst_len)){
    exec = exec_BGEZAL;

  }else if(!strncmp(line, "BLTZ", inst_len)){
    exec = exec_BLTZ;

  }else if(!strncmp(line, "BLTZAL", inst_len)){
    exec = exec_BLTZAL;

  }else if(!strncmp(line, "DIVU", inst_len)){
    exec = exec_DIVU;

  }else if(!strncmp(line, "LB", inst_len)){
    exec = exec_LB;

  }else if(!strncmp(line, "MULTU", inst_len)){
    exec = exec_MULTU;

  }else if(!strncmp(line, "ORI", inst_len)){
    exec = exec_ORI;

  }else if(!strncmp(line, "SB", inst_len)){
    exec = exec_SB;

  }else if(!strncmp(line, "SLLV", inst_len)){
    exec = exec_SLLV;

  }else if(!strncmp(line, "SLTI", inst_len)){
    exec = exec_SLTI;

  }else if(!strncmp(line, "SLTIU", inst_len)){
    exec = exec_SLTIU;

  }else if(!strncmp(line, "SLTU", inst_len)){
    exec = exec_SLTU;

  }else if(!strncmp(line, "SRA", inst_len)){
    exec = exec_SRA;

  }else if(!strncmp(line, "SRLV", inst_len)){
    exec = exec_SRLV;

  }else if(!strncmp(line, "SUBU", inst_len)){
    exec = exec_SUBU;

  }else if(!strncmp(line, "XORI", inst_len)){
    exec = exec_XORI;

  */}else{
    printf("ERREUR : Opération inconnu\n");
    //result = -1; //Cas d'erreur, il est impossible d'avoir 0xFFFFFFF0 dans les autres cas d'où l'utilisation de -1
  }

  //return result;
}

void execution(program prog){
  instruction* executed_instruction = prog->next;
  while(executed_instruction != NULL){
    (*(executed_instruction->exec))(executed_instruction->line_hexa);

    while(executed_instruction != NULL && executed_instruction->address != *pc){
      if(executed_instruction->address < *pc) executed_instruction = executed_instruction->next;
      else executed_instruction = executed_instruction->prev;
    }


  }
}
