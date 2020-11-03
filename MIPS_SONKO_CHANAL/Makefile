all: main.o function.o translation.o
	gcc -o emul-mips main.o function.o translation.o
	rm *.o
	rm *.gch

main.o: Code/main.c
	gcc -c Code/main.c -Wall

function.o: Code/function.c Code/function.h
	gcc -c Code/function.c -Wall

translation.o: Code/translation.c Code/translation.h
	gcc -c Code/translation.c -Wall

clear :
	rm *.o
	rm *.gch
