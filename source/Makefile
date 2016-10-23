CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wuninitialized -Werror -std=c99
OBJS=utility.o main.o
PROGNAME=bride_of_romput
STATICNAME=bride_of_romput_static

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGNAME)

.PHONY: static
static:
	$(CC) $(CFLAGS) -static $(OBJS) -o $(STATICNAME)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

.PHONY: clean
clean:
	rm *.o $(PROGNAME) $(STATICNAME)
