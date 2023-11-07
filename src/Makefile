CC	= mpicc
CFLAGS	= -g -Wall -std=c99
OUTPUT	= ../obj/

all: \
	mpihello \
	mpihellocomm \
	mpioutput \
	mpireduce \
	mpitrapezoid \
	mpimatrix \
	lab1sequential \
	lab1parallel

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

double_array: init double_array.c double_array.h
	$(CC) $(CFLAGS) -o $(OUTPUT)double_array.o -c double_array.c

mpimatrix: init double_array mpimatrix.c
	$(CC) $(CFLAGS) -o $(OUTPUT)mpimatrix mpimatrix.c $(OUTPUT)double_array.o

lab1: init lab1/lab1.c lab1/lab1.h
	$(CC) $(CFLAGS) -o $(OUTPUT)lab1.o -c lab1/lab1.c

lab1sequential: init lab1 lab1/lab1sequential.c
	$(CC) $(CFLAGS) -o $(OUTPUT)lab1sequential lab1/lab1sequential.c $(OUTPUT)lab1.o

lab1parallel: init lab1 lab1/lab1parallel.c
	$(CC) $(CFLAGS) -o $(OUTPUT)lab1parallel lab1/lab1parallel.c $(OUTPUT)lab1.o
	
clean:
	rm -f *~ *.o a.out
