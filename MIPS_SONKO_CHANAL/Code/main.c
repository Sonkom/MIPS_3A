#include "translation.h"
#include "function.h"

int main(int argc, char const *argv[]) {
  char test[] = "$zerfs";
  printf("%d\n", decode_reg(test));

  return 0;
}
