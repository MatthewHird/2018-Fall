LAB10: main.o
	g++ main.o -o LAB10

main.o: main.cpp
	g++ -c main.cpp -o main.o

run: LAB10 clean
	./LAB10

clean:
	rm -f *.o

cleanAll:
	rm -f *.o LAB10