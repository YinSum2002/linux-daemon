CC = gcc
CFLAGS = -Wall -Wextra -std=c11

monitor: main.c parser.c
	$(CC) $(CFLAGS) main.c parser.c -o monitor

clean:
	rm -f monitor