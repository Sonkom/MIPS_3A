// Gère la lecture du programme dans un fichier en entrée, et l'écriture du code hexadécimal dans un fichier en sortie

#include "translation.h"
#include "function.h"
#include "registers.h"
#include "memory.h"

#define LENLINE 20

typedef struct instruction instruction;

struct instruction {
  unsigned int address; /* Addresse de l'instruction */
  char line[LENLINE] ; /* contenue de la ligne */
  unsigned int line_hexa; /* traduction hexadécimal de l'instruction */
  instruction* next ; /* adresse du successeur */
  void (*exec)(int); /* Pointeur vers la fonction à exécuter */
};

typedef instruction* program;

/*------ UTILITAIRE À LA LISTE CHAINÉE ------*/

program init_program(void); //Crée et initalise la liste chaînée des instructions

instruction* add_instruct(program prog); //ajoute une instruction à la liste chaînée, retourne l'adresse de la case correspondant à l'instruction ajoutée

void free_prog(program prog); //Supprime la liste chapinée des instructions pour libérer la mémoire

void print_prog(program prog); //Affiche le programme mis dans la liste chaînée

/* ------ LECTURE + ÉCRITURE DE FICHIER ------ */

void read_file(char* name_source, program prog); //Fonction qui lit le fichier source et pose le résultat dans la liste chaînée program

void write_file(char* name_result, program prog); //Fonction qui écrit le résultat en hexadécimal de le fichier destination

/*---- ----*/

void translate_to_hexa(program prog); //Fonction qui traduit chaque ligne en son code hexadécimal et la met dans la liste chaînée (dans le champ line_hexa)

void execution_pointer_setup(program prog);

void instruct_execute_pointer(char *line, void (*exec)(int));

void execution(program prog);
