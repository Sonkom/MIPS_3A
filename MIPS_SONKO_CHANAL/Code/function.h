//Code concernant les fonctions utiles supplémentaires

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_to_int(char* str, int d, int f); //Convertie la chaine de caractère str[d:f] en un entier

int find_char_r(char* str, char c, int d, int f); //Retourne la position du caractère dans la chaîne passée en argument

void test_and_hexified(char** name_source, char** name_result); //Ajoute au noms des fichier entrée et sortie respectivement "tests/" et "hexified/" afin d'aller chercher les dossiers correspondant

int create_mask(int start, int end); //Permet de créer un masque composé de 1 entre le bit numéro "start" et le bit numéro "end"

void delete_end_spaces(char* sentence); //Supprimer les espaces à la fin du chaîne de caractères
