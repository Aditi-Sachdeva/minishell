CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

minishell: src/*.c include/*.h
	$(CC) $(CFLAGS) -o minishell src/*.c

clean:
	rm -f minishell