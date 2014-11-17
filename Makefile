all: test_ppm
test_ppm: test_ppm.c ppm.o
	gcc -Wall -o test_ppm.out test_ppm.c ppm_functions.o -lm
ppm.o: ppm.h ppm_functions.c 
	gcc -Wall -o  ppm_functions.o ppm_functions.c -c

