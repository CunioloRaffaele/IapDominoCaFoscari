# Non sta toccar.

CC = clang
CFLAGS = -Wall -Werror -std=c99 -O2 --pedantic

.PHONY: all clean

all: iap run

iap:
	$(CC) $(CFLAGS) *.c ./fragments/*.c ./functions/*.c -o iap

run: iap
	./iap --debugging

clean:
	rm -f *.o main ./iap

# https://youtu.be/yA8uXpZL-QM?feature=shared
# https://makefiletutorial.com