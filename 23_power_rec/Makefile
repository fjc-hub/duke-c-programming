main: power.o test-power.o
	gcc -o main -std=gnu99 -pedantic -Wall -Werror power.o test-power.o

power.o: power.c
	gcc -c -std=gnu99 -pedantic -Wall -Werror power.c

test-power.o: 
	ln -s ../22_tests_power/test-power.c ./
	gcc -c -std=gnu99 -pedantic -Wall -Werror test-power.c

.PHONY: clean
clean:
	echo 'clean object files'
	rm power.o test-power.o