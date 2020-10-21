all: main.o fonction.o traduction.o
	gcc -o emul-mips main.o fonction.o traduction.o

main.o: code/main.c
	gcc -c code/main.c -Wall

fonction.o: code/fonction.c code/fonction.h
	gcc -c code/fonction.c -Wall

traduction.o: code/traduction.c code/traduction.h
	gcc -c code/traduction.c -Wall
