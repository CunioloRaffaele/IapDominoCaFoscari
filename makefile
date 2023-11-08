# Non sta toccar.

CC = clang
CFLAGS = -Wall -Werror -std=c99

.PHONY: all clean

all: dominoIlC

dominoIlC: main.o functions.h
	$(CC) $(CFLAGS) -o dominoIlC main.c

main.o: main.c $(functions/*.h)
	$(CC) $(CFLAGS) -c main.c

run: dominoIlC
	./dominoIlC

clean:
	rm -f *.o main

# https://youtu.be/yA8uXpZL-QM?feature=shared
# https://makefiletutorial.com