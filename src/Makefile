CC		= mpicc
CFLAGS	= -g -Wall -std=c99

all: mpihello mpihellocomm

init:
	mkdir ../obj/

mpihello: init mpihello.c
	$(CC) $(CFLAGS) -o ../obj/mpihello mpihello.c

mpihellocomm: init mpihellocomm.c
	$(CC) $(CFLAGS) -o ../obj/mpihellocomm mpihellocomm.c

clean:
	rm -f *~ *.o a.out
