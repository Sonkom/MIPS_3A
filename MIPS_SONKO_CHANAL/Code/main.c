#include "translation.h"
#include "function.h"
#include "memory.h"


int main(int argc, char *argv[]) {

  char *name_source, *name_result;
  program prog;

  if (argc != 3) {
    printf("ERREUR : Nombre d'arguments non valide\n");
    printf("Il faut nom_du_fichier_source + nom_du_fichier_résultant (dans cet ordre là)\n");
  }
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
