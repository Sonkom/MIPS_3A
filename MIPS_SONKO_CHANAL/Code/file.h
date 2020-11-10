// Gère la lecture du programme dans un fichier en entrée, et l'écriture du code hexadécimal dans un fichier en sortie

#include "translation.h"
#include "function.h"

#define LENLINE 20

typedef struct instruction instruction;

struct instruction {
  unsigned int address; /* Addresse de l'instruction */
  char line[LENLINE] ; /* contenue de la ligne */
  int line_hexa; /* traduction hexadécimal de la ligne */
  instruction* next ; /* adresse du successeur */
};

typedef instruction* program;

/* ------ UTILITAIRE À LA LISTE CHAINÉE ------*/

program init_program(void); //Crée et initalise la liste chaînée des instructions

instruction* add_instruct(program prog); //ajoute une instruction à la liste chaînée, retourne l'adresse de la case correspondant à l'instruction ajoutée

void free_prog(program prog); //Supprime la liste chapinée des instructions pour libérer la mémoire

void print_prog(program prog); //Affiche le programme mis dans la liste chaînée

/* ------ LECTURE + ÉCRITURE DE FICHIER ------ */

void read_file(char* name_source, program prog); //Fonction qui lit le fichier source et pose le résultat dans la liste chaînée program

void translate_to_hexa(program prog); //Fonction qui traduit chaque ligne en son code hexadécimal et la met dans la liste chaînée (dans le champ line_hexa)

void write_file(char* name_result, program prog); //Fonction qui écrit le résultat en hexadécimal de le fichier destination
