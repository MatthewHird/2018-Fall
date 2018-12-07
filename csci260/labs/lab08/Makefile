LAB08: main.o
	g++ main.o -o LAB08

main.o: main.cpp
	g++ -c main.cpp -o main.o

run: LAB08 clean
	./LAB08

clean:
	rm -f *.o

cleanAll:
	rm -f *.o LAB08