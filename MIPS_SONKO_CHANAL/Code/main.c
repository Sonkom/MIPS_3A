#include "memory.h"


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
    print_prog(prog);

    translate_to_hexa(prog);

    write_file(name_result, prog);

    free_prog(prog);
  }

  return 0;
}
