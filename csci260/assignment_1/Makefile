pex1: main.o batch_queue.o job.o
	g++ main.o batch_queue.o job.o -o pex1

main.o: main.cpp batch_queue.h my_exceptions.h
	g++ -g -c main.cpp

batch_queue.o: batch_queue.cpp batch_queue.h priority_queue.h priority_queue.inl.h job.h my_exceptions.h
	g++ -g -c batch_queue.cpp

job.o: job.cpp job.h
	g++ -g -c job.cpp

clean:
	-rm *.o pex1