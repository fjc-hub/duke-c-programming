CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
	gcc -o $@ $(CFLAGS) $^
%.o: %.c
	gcc $(CFLAGS) -c $<
depend:
	makedepend cards.c  deck.c  eval.c  future.c  input.c  main.c
clean:
	rm -rf *.o poker *~
