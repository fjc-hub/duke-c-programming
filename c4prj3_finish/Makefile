# variables
CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)

poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
# '$@' is the name of the current target, add echo $@ to verify
# '$^' is all prerequisite names
	gcc -o $@ $(CFLAGS) $^

%.o: %.c
# '$<' is the name of the first prerequisite
	gcc $(CFLAGS) -c $< 

.PHONY: clean depend

depend:
	makedepend cards.c  deck.c  eval.c  future.c  input.c  main.c
clean:
	rm -rf *.o poker *~
