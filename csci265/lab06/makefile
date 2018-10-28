# lab 6 makefile
SHELL=/bin/bash
SRC=lab6
SRCFILES=$(shell echo ${SRC}{".cpp",".h",".txt"})
CC=g++
OPTIONS=-Wall

${SRC}x: ${SRC}.o
	${CC} ${OPTIONS} ${SRC}.o -o ${SRC}x

${SRC}.o: ${SRC}.cpp ${SRC}.h
	${CC} ${OPTIONS} -c ${SRC}.cpp

listSrcFiles: 
	 @ls -l ${SRCFILES}

clean:
	-rm ${SRC}.o

cleanx:
	-rm ${SRC}{"x",".o"}

submit:
	git add -v ${SRC}.cpp ${SRC}.h ${SRC}.txt makefile README
	git commit -m "Submit ${SRC}"
	git push --all origin