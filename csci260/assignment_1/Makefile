pex1: main.o batch_queue.o job.o
	g++ main.o batch_queue.o job.o -o pex1

main.o: main.cpp batch_queue.h
	g++ -c main.cpp

batch_queue.o: batch_queue.cpp batch_queue.h priority_queue.h priority_queue.inl.h min_heap.h min_heap.inl.h job.h
	g++ -c batch_queue.cpp

job.o: job.cpp job.h
	g++ -c job.cpp

clean:
	-rm *.o pex1