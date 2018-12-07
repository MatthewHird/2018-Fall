LAB09: main.o
	g++ main.o -o LAB09

main.o: main.cpp
	g++ -c main.cpp -o main.o

run: LAB09 clean
	./LAB09

clean:
	rm -f *.o

cleanAll:
	rm -f *.o LAB09