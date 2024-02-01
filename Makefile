CC = gcc
LDFLAGS = -lm
main: main.c
	gcc -Wall -Werror -std=c99 main.c -o main /usr/lib/x86_64-linux-gnu/libm.so

clean:
	rm -f main
