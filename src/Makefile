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
	omptrapezoid \
	omppi \
	ompblocks

init:
	mkdir -p $(OUTPUT)

mpihello: init mpihello.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpihello mpihello.c

mpihellocomm: init mpihellocomm.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpihellocomm mpihellocomm.c

mpioutput: init mpioutput.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpioutput mpioutput.c

mpireduce: init mpireduce.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpireduce mpireduce.c

mpitrapezoid: init mpitrapezoid.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpitrapezoid mpitrapezoid.c

mpimatrix: init mpimatrix.c
	$(MPICC) $(CFLAGS) -o $(OUTPUT)mpimatrix mpimatrix.c

omptrapezoid: init omptrapezoid.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)omptrapezoid omptrapezoid.c

omppi: init omppi.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)omppi omppi.c

ompblocks: init ompblocks.c
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $(OUTPUT)ompblocks ompblocks.c
	
clean:
	rm -f *~ ../obj/* *.txt a.out
