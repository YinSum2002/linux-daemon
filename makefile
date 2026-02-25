CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -O0

monitor: main.c parser.c
	$(CC) $(CFLAGS) main.c parser.c cpu_stats.c -o monitor -pthread

clean:
	rm -f monitor