all: main.o function.o translation.o file.o
	gcc -o emul-mips main.o function.o translation.o file.o
	rm *.o

main.o: Code/main.c
	gcc -g -c Code/main.c -Wall

function.o: Code/function.c Code/function.h
	gcc -g -c Code/function.c -Wall

translation.o: Code/translation.c Code/translation.h
	gcc -g -c Code/translation.c -Wall

file.o: Code/file.c Code/file.h
	gcc -g -c Code/file.c -Wall

clear :
	rm *.o
