all: frequency
frequency: trietxt.c
	gcc -Wall trietxt.c -o frequency
clean: 
	rm frequency