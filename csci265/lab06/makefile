# lab 6 makefile
SHELL=/bin/bash

lab6x: lab6.o
	g++ -Wall lab6.o -o lab6x

lab6.o: lab6.cpp lab6.h
	g++ -Wall -c lab6.cpp

clean:
	-rm lab6.o

cleanx:
	-rm lab6x lab6.o

submit:
	git add -v lab6.cpp lab6.h lab6.txt makefile README
	git commit -m "Submit lab06"
	git push --all origin