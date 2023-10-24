CC		= gcc
CFLAGS	= -Wall

all: \
	problem1 \
	problem2
	
problem1: \
	problem1.c \
	problem1.s

	$(CC) $(CFLAGS) -o $@ $@.c $@.s

problem2: \
	problem2.c \
	problem2.s

	$(CC) $(CFLAGS) -o $@ $@.c $@.s

clean:
	rm -f *~ *.o a.out core problem1 problem2
