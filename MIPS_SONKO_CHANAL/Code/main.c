#include "translation.h"
#include "function.h"
#include "memory.h"


int main(int argc, char *argv[]) {

  char *name_source, *name_result;
  program prog;

  if (argc < 3) printf("ERREUR : Arguments manquants\n");
  else {

    name_source = *(argv+1);
    name_result = *(argv+2);
    prog = init_program();

    read_file(name_source, prog);
    print_prog(prog);

    translate_to_hexa(prog);

    write_file(name_result, prog);

    free_prog(prog);
  }

  return 0;
}
