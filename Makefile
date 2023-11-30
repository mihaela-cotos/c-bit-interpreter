CFLAGS=-lm

all: decode encode execute

decode: decode.c
	gcc decode.c $(CFLAGS) -o decode

task2: encode.c
	gcc encode.c $(CFLAGS) -o encode

execute: execute.c
	gcc execute.c $(CFLAGS) -o execute


clean:
	rm -f decode encode execute

zip:
	zip miniprocesor.zip decode.c encode.c \
	execute.c README.md Makefile
