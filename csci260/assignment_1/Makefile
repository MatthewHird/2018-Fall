pex1: main.o batch_queue.o job.o my_exceptions.o
	g++ main.o batch_queue.o job.o my_exceptions.o -o pex1

main.o: main.cpp batch_queue.h my_exceptions.h
	g++ -c main.cpp

batch_queue.o: batch_queue.cpp batch_queue.h priority_queue.h priority_queue.inl.h job.h my_exceptions.h
	g++ -c batch_queue.cpp

job.o: job.cpp job.h
	g++ -c job.cpp

my_exceptions.o: my_exceptions.cpp my_exceptions.h
	g++ -c my_exceptions.cpp

clean:
	-rm *.o pex1