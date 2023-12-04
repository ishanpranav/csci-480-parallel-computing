CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 -fopenmp

all: genprimes

genprimes:
	$(CC) $(CFLAGS) -o genprimes genprimes.c
	
clean:
	rm -f *.o *~ *.txt a.out genprimes
