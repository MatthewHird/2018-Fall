pex3: main.o social_influence_analyzer.o influence_graph.o
	g++ main.o social_influence_analyzer.o influence_graph.o -o pex3

main.o: main.cpp stack.h stack.inl.h
	g++ -c main.cpp

social_influence_analyzer.o: social_influence_analyzer.cpp social_influence_analyzer.h influence_graph.h my_exceptions.h
	g++ -c social_influence_analyzer.cpp

influence_graph.o: influence_graph.cpp influence_graph.h stack.h stack.inl.h my_exceptions.h
	g++ -c influence_graph.cpp

clean:
	-rm *.o pex3