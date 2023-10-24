CC	= mpicc
CFLAGS	= -g -Wall -std=c99
OUTPUT	= ../obj/

all: mpihello mpihellocomm mpioutput

init:
	mkdir -p $(OUTPUT)

mpihello: init mpihello.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpihello mpihello.c

mpihellocomm: init mpihellocomm.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpihellocomm mpihellocomm.c

mpioutput: init mpioutput.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpioutput mpioutput.c

clean:
	rm -f *~ *.o a.out
