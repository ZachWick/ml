# Makefile for wmm

LS = /bin/ls
LSLOC = /bin
GNU_PREFIX = 'gnu_'
INSTALL_LOC = /usr/local/bin

build: ml

clean:
	rm -f ml ml.o

doc:
	docco ./*.c

test: build
	valgrind --leak-check=full --show-leak-kinds=all ./ml

ml: ml.o
	gcc -std=gnu99 -g $< -o $@ -Wall

main.o: ml.c
	gcc -std=gnu99 -g -c $< -o $@ -Wall

install:
	rm -f $(INSTALL_LOC)/ml
	cp ml $(INSTALL_LOC)/ml

replace_gnu: install
	mv $(LS) $(LSLOC)/$(GNU_PREFIX)ls
	ln -s $(INSTALL_LOC)/ml $(INSTALL_LOC)/ls
