CC		= gcc
CFLAGS	= -g -Wall -std=c99
CLIBS	= -lm 

all: problem1 problem2

problem1: problem1.c bst.o bst.h
	$(CC) $(CFLAGS) -o problem1 problem1.c bst.o

problem2: problem2.c float.o float.h
	$(CC) $(CFLAGS) -o problem2 problem2.c float.o $(CLIBS) 

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

float.o: float.c float.h
	$(CC) $(CFLAGS) -c float.c

run_problem1: problem1
	./problem1 < test1.txt

run_problem2: problem2
	./problem2 < test2.txt

clean:
	rm -f *~ *.o a.out core problem1 problem2
