#include "file.h"


int main(int argc, char *argv[]) {

  char *name_source, *name_result;
  instruction* interactive;
  char step_to_step_mode = 0; //0 pour directe, 1 pour pas à pas
  char error_check = 0, detect_enter = 0;
  program prog;
  char input = '\0';
  printf("          ----------MIPS EMULATOR----------          \n");

  if (argc > 3) printf("ERROR : Unvalid numbers of arguments => Please specify the source file and the mode (if needed)\n");
  else if (argc >= 2) {
    data_counter = 0;
    name_source = *(argv+1);
    name_result = *(argv+1);

    if (argc == 3){
      if (strcmp(argv[2],"-pas")) {
        printf("Unknown mode : please mark '-pas' if you want the step_to_step mode\n\nQuitting program");
        error_check = 1;
      }
      else step_to_step_mode = 1;
    }
    if (!error_check){
      test_and_hexified(&name_source, &name_result);

      prog = init_program();

      printf("\nSource file : %s\nThe output will be written in : %s\n\n",name_source, name_result);

      read_file(name_source, prog, step_to_step_mode);

      //translate_to_hexa(prog);
      execution_pointer_setup(prog);

      write_file(name_result, prog);

      init_registers();
      init_data_memory();

      print_prog(prog);

      printf("**** Press [enter] to start execute ****\n");
      scanf("%c",&input);

      execution(prog, step_to_step_mode);
      printf("\n          Final processor state :\n\n");
      print_registers();
      print_memory();

      printf("\nProgram finished.\n\n");


      free_memory();
      free_prog(prog);
    }
  }
  else {
    printf("\n---- You are in the interactive mode of the MIPS emulator.");
    printf("\n---- If you want to use a program file, please exit and use './emul-mips your_file -pas (optionnal)'\n");
    printf("---- Please note that your file should be in the 'tests' directory.\n");

    init_registers();
    init_data_memory();

    interactive = (instruction *)malloc(sizeof(struct instruction));
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
    free_memory();
  }

  printf("--------- Quitting emulator ---------\n");
  return 0;
}
