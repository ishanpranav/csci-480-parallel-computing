CC			= gcc
MPICC		= mpicc
CFLAGS		=  -g -Wall -std=c99
OMPFLAGS	=  -fopenmp
OUTPUT	= ../obj/

all: \
	mpihello \
	mpihellocomm \
	mpioutput \
	mpireduce \
	mpitrapezoid \
	mpimatrix \
	lab1sequential \
	lab1parallel \
	omptrapezoid \
	omppi \
	lab2sequential

init:
	mkdir -p $(OUTPUT)

mpihello: init mpihello.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpihello mpihello.c

mpihellocomm: init mpihellocomm.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpihellocomm mpihellocomm.c

mpioutput: init mpioutput.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpioutput mpioutput.c

single_array: init single_array.c single_array.h
	$(CC) $(CFLAGS) -o $(OUTPUT)single_array.o -c single_array.c

mpireduce: init single_array mpireduce.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpireduce mpireduce.c $(OUTPUT)single_array.o

mpitrapezoid: init mpitrapezoid.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpitrapezoid mpitrapezoid.c

double_array: init double_array.c double_array.h
	$(CC) $(CFLAGS) -o $(OUTPUT)double_array.o -c double_array.c

mpimatrix: init double_array mpimatrix.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpimatrix mpimatrix.c $(OUTPUT)double_array.o

lab1: init lab1/lab1.c lab1/lab1.h
	$(CC) $(CFLAGS) -o $(OUTPUT)lab1.o -c lab1/lab1.c

lab1sequential: init lab1 lab1/lab1sequential.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)lab1sequential lab1/lab1sequential.c $(OUTPUT)lab1.o

lab1parallel: init lab1 lab1/lab1parallel.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)lab1parallel lab1/lab1parallel.c $(OUTPUT)lab1.o

omptrapezoid: init omptrapezoid.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)omptrapezoid omptrapezoid.c

int_array: init int_array.c int_array.h
	$(CC) $(CFLAGS) -o $(OUTPUT)int_array.o -c int_array.c

exception: init exception.c exception.h
	$(CC) $(CFLAGS) -o $(OUTPUT)exception.o -c exception.c

random: init exception random.c random.h
	$(CC) $(CFLAGS) -o $(OUTPUT)random.o -c random.c

omppi: init random int_array omppi.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)omppi omppi.c $(OUTPUT)int_array.o $(OUTPUT)random.o $(OUTPUT)exception.o

lab2sequential: init int_array lab2/lab2sequential.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)lab2sequential lab2/lab2sequential.c $(OUTPUT)int_array.o

clean:
	rm -f *~ *.o a.out
