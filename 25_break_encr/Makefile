breaker: breaker.c
	gcc -o breaker -std=gnu99 -Wall -Werror breaker.c

leakSummry: breaker input.txt
	valgrind -s ./breaker input.txt
