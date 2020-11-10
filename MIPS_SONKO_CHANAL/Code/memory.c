//Gère la mémoire de données

#include "memory.h"

void init_registers(){
   zero = registers+0; /* Registre ZERO (toujours nul) */
   at = registers+1;  /* Assembler tempory*/
  // Retour d'une sous-routine :
   v0 = registers+2;
   v1 = registers+3;
  // Arguments d'une sous-routine :
   a0 = registers+4;
   a1 = registers+5;
   a2 = registers+6;// Gère la lecture du programme dans un fichier en entrée, et l'écriture du code hexadécimal dans un fichier en sortie

   a3 = registers+7;
  // Registres temporaires
   t0 = registers+8;
   t1 = registers+9;
   t2 = registers+10;
   t3 = registers+11;
   t4 = registers+12;
   t5 = registers+13;
   t6 = registers+14;
   t7 = registers+15;
  // Registres temporaires préservés par les sous-routines
   s0 = registers+16;
   s1 = registers+17;
   s2 = registers+18;
   s3 = registers+19;
   s4 = registers+20;
   s5 = registers+21;
   s6 = registers+22;
   s7 = registers+23;
  // Deux temporaires supplémentaires
   t8 = registers+24;
   t9 = registers+25;
  // Kernel (réservés !)
   k0 = registers+26;
   k1 = registers+27;

   gp = registers+28; /* Global Pointer */
   sp = registers+29; /* Stack Pointer */
   fp = registers+30; /* Frame Pointer */
   ra = registers+31; /* Return Adress */
  // Registres de stockage pour des opérations entre deux données de 32 bits;
   hi = registers+32;
   lo = registers+33;

   pc = registers+34; /* PROGRAM COUNTER */

   /* Creation du tableau du nom des registres */
   registers_name[0] = "zero";
   registers_name[1] = "  at";
   registers_name[2] = "  v0";
   registers_name[3] = "  v1";
   registers_name[4] = "  a0";
   registers_name[5] = "  a1";
   registers_name[6] = "  a2";
   registers_name[7] = "  a3";
   registers_name[8] = "  t0";
   registers_name[9] = "  t1";
   registers_name[10] = "  t2";
   registers_name[11] = "  t3";
   registers_name[12] = "  t4";
   registers_name[13] = "  t5";
   registers_name[14] = "  t6";
   registers_name[15] = "  t7";
   registers_name[16] = "  s0";
   registers_name[17] = "  s1";
   registers_name[18] = "  s2";
   registers_name[19] = "  s3";
   registers_name[20] = "  s4";
   registers_name[21] = "  s5";
   registers_name[22] = "  s6";
   registers_name[23] = "  s7";
   registers_name[24] = "  t8";
   registers_name[25] = "  t9";
   registers_name[26] = "  k0";
   registers_name[27] = "  k1";
   registers_name[28] = "  gp";
   registers_name[29] = "  sp";
   registers_name[30] = "  fp";
   registers_name[31] = "  ra";
   registers_name[32] = "  hi";
   registers_name[33] = "  lo";
   registers_name[34] = "  pc";

  for(int i=0; i<NBR_REGISTERS; i++) registers[i]=0; //Initialisation de la valeur des registres à 0
}

void print_registers(){
  printf("Etat des registres :\n");
  for(int i=0; i<NBR_REGISTERS; i++){
    printf(" %s : 0x%.8x",registers_name[i], registers[i]);
    if((i%4==3 && i != 0) || i+1==NBR_REGISTERS) printf("\n");
  }
}

int read_register(int index_register){
  return registers[index_register];
}

void write_register(int index_register, int value){
  registers[index_register] = value;
}
