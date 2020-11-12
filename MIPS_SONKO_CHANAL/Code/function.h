//Code concernant les fonctions utiles supplémentaires

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_to_int(char* str, int d, int f);

int find_char_r(char* str, char c, int d, int f);

void test_and_hexified(char** name_source, char** name_result);

//Permet de créer un masque composé de 1 entre le bit numéro "start" et le bit numéro "end"
int create_mask(int start, int end);
