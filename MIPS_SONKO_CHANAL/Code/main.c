#include "registers.h"


int main(int argc, char *argv[]) {

  init_registers();
  print_registers();
  exec_ADDI(0x20080001);
  exec_ADDI(0x20070001);
  exec_BEQ(0x10e80010);
  print_registers();

/*
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
    write_file(name_result, prog);

    print_prog(prog);
    printf("**** Press enter to start execute **** (soon)\n");

    free_prog(prog);
  }
*/
  return 0;
}
