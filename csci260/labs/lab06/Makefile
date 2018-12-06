sortPro: main.o
	g++ main.o -o sortPro

main.o: main.cpp
	g++ -c main.cpp -o main.o

run: sortPro clean
	./sortPro

clean:
	rm -f *.o

cleanAll:
	rm -f *.o sortPro