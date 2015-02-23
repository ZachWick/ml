# Makefile for wmm

build: ml

clean:
	rm -f ml ml.o

ml: ml.o
	gcc -std=gnu99 -g $< -o $@ -Wall

main.o: ml.c
	gcc -std=gnu99 -g -c $< -o $@ -Wall

install:
	rm -f /usr/local/bin/ml
	cp ml /usr/local/bin/ml
