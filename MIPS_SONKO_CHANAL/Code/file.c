// Gère la lecture du programme dans un fichier en entrée, l'écriture du code hexadécimal dans un fichier en sortie, et le programme entier (exécution du programme) => Liste chainée program

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
  instruction* instruct = NULL;
  while (last->next != NULL) last = last->next;

  if ((data_counter == 0x0) && (last != prog)) printf("ERROR : The memory's capacity has reached its limits\n");
  else {
    instruct = (instruction *)malloc(sizeof(instruction));
    instruct->next = NULL;

    while (last->next != NULL) last = last->next;
    last->next = instruct;
  }
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
  printf("\n");
}

/* ------ LECTURE + ÉCRITURE DE FICHIER ------ */

void read_file(char* name_source, program prog, char step_to_step_mode){
  FILE *file_source;
  char character, *read_line = NULL;
  int index = 0, is_comment = 0;
  char overflow_check = 1, input = '\0', skip = 0;
  unsigned int instruct_address = 0;
  instruction* instruct = NULL;

  file_source = fopen(name_source, "r");
  if(file_source == NULL) {
    perror("File reading problem");
    exit(1);
  }

  while (!feof(file_source) && overflow_check) {

    fscanf(file_source, "%c", &character);

    if(character != '\n' && character != '\r'){

      if (character == '#') is_comment = 1;
      if (!is_comment && (!((index == 0) && (character == ' '))))
        {
          if (instruct == NULL){
            instruct = add_instruct(prog);
            if (instruct == NULL) overflow_check = 0;
            else {
              read_line = instruct->line;
              instruct->address = instruct_address;
              instruct_address+=4;
              data_counter+=4;
            }
          }
          read_line[index] = character;
          index++;
        }

    } else {
      if (read_line != NULL) read_line[index] = '\0';
      is_comment = 0;


      if (index != 0) {
        index = 0;
        instruct->line_hexa = translate(instruct->line);

        if (step_to_step_mode && !skip) {
          input = '\0';
          printf("\nAssembling line n°%d\n %s { hexadecimal instruction code : %.8x }\n",(instruct->address)/4,instruct->line,instruct->line_hexa);
          printf("\n--- Press [enter] to continue or [s] if you want to skip to the start of the execution\n");
          scanf("%c",&input);
          if (input == 's') skip = 1;
        }
        instruct = NULL;
        read_line = NULL;

      }
    }
  }
  fclose(file_source);
}

void write_file(char* name_result, program prog){
  instruction* file_writer = prog->next;
  FILE *file_result;
  int success = 1;

  file_result = fopen(name_result, "w");
  if(file_result == NULL) {
    perror("File opening problem");
    exit(1);
  }

  while ((file_writer != NULL) && success){
    if (file_writer->line_hexa != -1) fprintf(file_result, "%.8x\n",file_writer->line_hexa);
    else success = 0;
    file_writer = file_writer->next;
  }
  fclose(file_result);
}

/*---- TRADUCTION HEXA + EXECUTION PROGRAMME ----*/

/*void translate_to_hexa(program prog){
  instruction* translater = prog->next;

  while(translater != NULL) {
    translater->line_hexa = translate(translater->line);
    translater = translater->next;
  }
}*/

void execution_pointer_setup(program prog){
  instruction* setup_pointer = prog->next;

  while(setup_pointer != NULL) {
    instruct_execute_pointer(setup_pointer->line, &(setup_pointer->exec));
    setup_pointer = setup_pointer->next;
  }
}

void instruct_execute_pointer(char *line, int (**exec)(int)){
  int inst_len,i=0;

  while(*(line+i) != ' ' && *(line+i+1) != '\0') i++;
  inst_len=i;


  if(!strncmp(line, "NOP",inst_len)){
    *exec = &exec_NOP;

  }else if(!strncmp(line, "ADD", inst_len)){
    *exec = &exec_ADD;

  }else if(!strncmp(line, "AND", inst_len)){
    *exec = &exec_AND;

  }else if(!strncmp(line, "JR", inst_len)){
    *exec = &exec_JR;

  }else if(!strncmp(line, "MFHI", inst_len)){
    *exec = &exec_MFHI;

  }else if(!strncmp(line, "MFLO", inst_len)){
    *exec = &exec_MFLO;

  }else if(!strncmp(line, "MULT", inst_len)){
    *exec = &exec_MULT;

  }else if(!strncmp(line, "OR", inst_len)){
    *exec = &exec_OR;

  }else if(!strncmp(line, "DIV", inst_len)){
    *exec = &exec_DIV;

  }else if(!strncmp(line, "ROTR", inst_len)){
    *exec = &exec_ROTR;

  }else if(!strncmp(line, "SLL", inst_len)){
    *exec = &exec_SLL;

  }else if(!strncmp(line, "SLT", inst_len)){
    *exec = &exec_SLT;

  }else if(!strncmp(line, "SRL", inst_len)){
    *exec = &exec_SRL;

  }else if(!strncmp(line, "SUB", inst_len)){
    *exec = &exec_SUB;

  }else if(!strncmp(line, "XOR", inst_len)){
    *exec = &exec_XOR;

  }else if(!strncmp(line, "ADDI", inst_len)){
    *exec = &exec_ADDI;

  }else if(!strncmp(line, "BEQ", inst_len)){
    *exec = &exec_BEQ;

  }else if(!strncmp(line, "BGTZ", inst_len)){
    *exec = &exec_BGTZ;

  }else if(!strncmp(line, "BLEZ", inst_len)){
    *exec = &exec_BLEZ;

  }else if(!strncmp(line, "BNE", inst_len)){
    *exec = &exec_BNE;

  }else if(!strncmp(line, "LUI", inst_len)){
    *exec = &exec_LUI;

  }else if(!strncmp(line, "SW", inst_len)){
    *exec = &exec_SW;

  }else if(!strncmp(line, "LW", inst_len)){
    *exec = &exec_LW;

  }else if(!strncmp(line, "J", inst_len)){
    *exec = &exec_J;

  }else if(!strncmp(line, "JAL", inst_len)){
    *exec = &exec_JAL;

  }else if(!strncmp(line, "ADDIU", inst_len)){
    *exec = &exec_ADDIU;

  }else if(!strncmp(line, "ADDU", inst_len)){
    *exec = &exec_ADDU;

  }else if(!strncmp(line, "ANDI", inst_len)){
    *exec = &exec_ANDI;

  }else if(!strncmp(line, "BGEZ", inst_len)){
    *exec = &exec_BGEZ;

  }else if(!strncmp(line, "BGEZAL", inst_len)){
    *exec = &exec_BGEZAL;

  }else if(!strncmp(line, "BLTZ", inst_len)){
    *exec = &exec_BLTZ;

  }else if(!strncmp(line, "BLTZAL", inst_len)){
    *exec = &exec_BLTZAL;

  }else if(!strncmp(line, "DIVU", inst_len)){
    *exec = &exec_DIVU;

  }else if(!strncmp(line, "LB", inst_len)){
    *exec = &exec_LB;

  }else if(!strncmp(line, "MULTU", inst_len)){
    *exec = &exec_MULTU;

  }else if(!strncmp(line, "ORI", inst_len)){
    *exec = &exec_ORI;

  }else if(!strncmp(line, "SB", inst_len)){
    *exec = &exec_SB;

  }else if(!strncmp(line, "SLLV", inst_len)){
    *exec = &exec_SLLV;

  }else if(!strncmp(line, "SLTI", inst_len)){
    *exec = &exec_SLTI;

  }else if(!strncmp(line, "SLTIU", inst_len)){
    *exec = &exec_SLTIU;

  }else if(!strncmp(line, "SLTU", inst_len)){
    *exec = &exec_SLTU;

  }else if(!strncmp(line, "SRA", inst_len)){
    *exec = &exec_SRA;

  }else if(!strncmp(line, "SRLV", inst_len)){
    *exec = &exec_SRLV;

  }else if(!strncmp(line, "SUBU", inst_len)){
    *exec = &exec_SUBU;

  }else if(!strncmp(line, "XORI", inst_len)){
    *exec = &exec_XORI;

  }else{
    printf("ERREUR : Opération inconnu\n");
    //result = -1; //Cas d'erreur, il est impossible d'avoir 0xFFFFFFF0 dans les autres cas d'où l'utilisation de -1
  }

  //return result;
}

void execution(program prog, char step_to_step_mode){
  instruction* executed_instruction = prog->next;
  char input = '\0';
  int error = 0;

  while(executed_instruction != NULL  && error == 0){
    printf("Processing instruction:\n%.8x  { %s }\n\n",executed_instruction->line_hexa, executed_instruction->line);
    error = (*(executed_instruction->exec))(executed_instruction->line_hexa);

    if(error) printf("Exception occurs at 0x%x :\n", executed_instruction->address);
    print_error(error);

    while(executed_instruction != NULL && executed_instruction->address != *pc && error == 0){
      if(executed_instruction->address < *pc) executed_instruction = executed_instruction->next;
      else executed_instruction = executed_instruction->prev;
    }

    if (step_to_step_mode) {
      input = '\0';
      printf(" --- [r] : display registers; [m] : display memory; [n] : display next instruction; [c] : continue\n");
      while (input != 'c'){
        scanf("%c",&input);
        switch(input) {
          case 'r' :
            print_registers();
            break;
          case 'm' :
            print_memory();
            break;
          case 'n' :
            if (executed_instruction != NULL) printf("Next instruction is :\n%.8x  { %s }\n\n",executed_instruction->line_hexa, executed_instruction->line);
            else printf("Next instruction is : end of program\n");
            break;
        }
      }
    }

  }

}

void interactive_mode(void){
  char input = '\0',  detect_enter = 0;
  instruction *interactive = (instruction *)malloc(sizeof(struct instruction));
  interactive->address = 0x0;
  interactive->next = NULL;
  interactive->prev = NULL;

  while (strncmp(interactive->line,"EXIT",4)) {
    printf("\nEnter your instruction ([EXIT] if you want to quit the emulator):\n");
    fgets(interactive->line, LENLINE, stdin);
    if (strncmp(interactive->line,"EXIT",4)){
      interactive->line[find_char_r(interactive->line, '\n', 0, LENLINE)] = '\0';

      interactive->line_hexa = translate(interactive->line);
      instruct_execute_pointer(interactive->line, &(interactive->exec));

      printf("Processing instruction:\n%.8x  { %s }\n\n",interactive->line_hexa, interactive->line);
      (*(interactive->exec))(interactive->line_hexa);

      printf("\n--- [enter] to continue ; [r] to print registers ; [m] to print memory\n");
      do {
        fflush(stdin);
        input = fgetc(stdin);
        fflush(stdin);
        switch(input) {
          case 'r' :
            print_registers();
            detect_enter = 0;
            break;
          case 'm' :
            print_memory();
            detect_enter = 0;
            break;
          case '\n' :
            detect_enter = 1;
            break;
        }
        if (!detect_enter) {
          fflush(stdin);
          input = fgetc(stdin);
          fflush(stdin);
        }
      } while ((input == 'r') || (input == 'm') || ((input == '\n') && !detect_enter));
      detect_enter = 0;
    }
  }
  free(interactive);
}

void print_error(int code){
  switch (code) {
    case 0b10:
      printf("ERROR 10 : Signed integer overflow\n");
      break;
    case 0b11:
      printf("ERROR 11 : Signed integer underflow\n");
      break;
    case 0b100:
      printf("ERROR 100 : Illegal address\n");
      break;
    default:
      break;
  }
}
