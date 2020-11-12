#include "file.h"


int main(int argc, char *argv[]) {

  char *name_source, *name_result;
  program prog;

  if (argc != 2) printf("ERREUR : Nombre d'arguments non valide => Il nous faut que le fichier source\n");
  else {

    name_source = *(argv+1);
    name_result = *(argv+1);
    test_and_hexified(&name_source, &name_result);
    prog = init_program();


    read_file(name_source, prog);
    translate_to_hexa(prog);

    execution_pointer_setup(prog);
    
    write_file(name_result, prog);

    init_registers();
    init_data_memory();

    print_prog(prog);
    printf("**** Press enter to start execute **** (soon)\n");


    execution(prog);
    print_registers();


    free_prog(prog);
  }

  return 0;
}
