CC	= mpicc
CFLAGS	= -g -Wall -std=c99
OUTPUT	= ../obj/

all: \
	mpihello \
	mpihellocomm \
	mpioutput \
	mpireduce \
	mpitrapezoid

init:
	mkdir -p $(OUTPUT)

mpihello: init mpihello.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpihello mpihello.c

mpihellocomm: init mpihellocomm.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpihellocomm mpihellocomm.c

mpioutput: init mpioutput.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpioutput mpioutput.c

single_array: init single_array.c single_array.h
	$(CC) $(CFLAGS) -o $(OUTPUT)single_array.o -c single_array.c

mpireduce: init single_array mpireduce.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpireduce mpireduce.c $(OUTPUT)single_array.o

mpitrapezoid: init mpitrapezoid.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpitrapezoid mpitrapezoid.c

clean:
	rm -f *~ *.o a.out
