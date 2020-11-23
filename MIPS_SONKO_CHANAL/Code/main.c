#include "file.h"


int main(int argc, char *argv[]) {

  char *name_source, *name_result, *interactive_line_instruct;
  char step_to_step_mode = 0; //0 pour directe, 1 pour pas à pas
  char error_check = 0;
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
    printf("----Please note that your file should be in the 'tests' directory.\n");

    interactive_line_instruct = (char *)malloc(sizeof(char) * LENLINE);

    while (strncmp(interactive_line_instruct,"EXIT",4)) {
      printf("\nEnter your instruction ([EXIT] if you want to quit the emulator):\n");
      fgets(interactive_line_instruct, LENLINE, stdin);
      printf("VOICI : %s\n",interactive_line_instruct);
    }


  }

  return 0;
}
