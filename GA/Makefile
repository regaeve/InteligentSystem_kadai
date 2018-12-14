CFLAGS = -g -Wall

all:	GA

GA:	main.o GA.o initilize.o calcFitness.o
	gcc -o $@ $^

clean:
	rm *.o GA
