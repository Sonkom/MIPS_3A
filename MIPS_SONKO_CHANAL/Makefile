all: main.o function.o translation.o
	gcc -o emul-mips main.o function.o translation.o

main.o: code/main.c
	gcc -c code/main.c -Wall

function.o: code/function.c code/function.h
	gcc -c code/function.c -Wall

translation.o: code/translation.c code/translation.h
	gcc -c code/translation.c -Wall
