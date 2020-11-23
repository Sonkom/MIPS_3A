// Gère la lecture du programme dans un fichier en entrée, l'écriture du code hexadécimal dans un fichier en sortie, et le programme entier (exécution du programme) => Liste chainée program

#include "registers.h"

#define LENLINE 30

typedef struct instruction instruction;

struct instruction {
  unsigned int address; /* Addresse de l'instruction */
  char line[LENLINE] ; /* contenue de la ligne */
  unsigned int line_hexa; /* traduction hexadécimal de l'instruction */
  instruction* prev; /* pointe vers l'instruction précédente */
  instruction* next; /* pointe vers l'instruction suivante */
  void (*exec)(int); /* Pointeur vers la fonction à exécuter */
};

typedef instruction* program;

/*------ UTILITAIRE À LA LISTE CHAINÉE ------*/

program init_program(void); //Crée et initalise la liste chaînée des instructions

instruction* add_instruct(program prog); //ajoute une instruction à la liste chaînée, retourne l'adresse de la case correspondant à l'instruction ajoutée

void free_prog(program prog); //Supprime la liste chapinée des instructions pour libérer la mémoire

void print_prog(program prog); //Affiche le programme mis dans la liste chaînée

/* ------ LECTURE + ÉCRITURE DE FICHIER ------ */

void read_file(char* name_source, program prog, char step_to_step_mode); //Fonction qui lit le fichier source et pose le résultat dans la liste chaînée program

void write_file(char* name_result, program prog); //Fonction qui écrit le résultat en hexadécimal de le fichier destination

/*---- TRADUCTION HEXA + EXECUTION PROGRAMME ----*/

//void translate_to_hexa(program prog); //Fonction qui traduit chaque ligne en son code hexadécimal et la met dans la liste chaînée (dans le champ line_hexa)

void instruct_execute_pointer(char *line, void (**exec)(int)); //Fonction qui modifie le pointeur de fonction de telle sorte qu'elle pointe vers la fonction correspondante

void execution_pointer_setup(program prog); //Fonction qui setup les pointeurs de fonction pour chaque instruction

void execution(program prog, char step_to_step_mode); //Execute l'ensemble des instructions d'un programme
