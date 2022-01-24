CC=gcc -Wall -Wextra -pedantic

automaton: main.o
	$(CC) -o $@ $^

main.o: stack.o action.o
stack.o: stack.h
action.o: action.h