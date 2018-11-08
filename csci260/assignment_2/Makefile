pex2: main.o university_records.o string_id_bst.o two_four_tree.o student.o
	g++ main.o university_records.o string_id_bst.o two_four_tree.o student.o -o pex2

main.o: main.cpp university_records.h
	g++ -g -c main.cpp

university_records.o: university_records.cpp university_records.h string_id_bst.h two_four_tree.h student.h my_exceptions.h
	g++ -g -c university_records.cpp

string_id_bst.o: string_id_bst.cpp string_id_bst.h student.h
	g++ -g -c string_id_bst.cpp

two_four_tree.o: two_four_tree.cpp two_four_tree.h student.h
	g++ -g -c two_four_tree.cpp

student.o: student.cpp student.h my_exceptions.h
	g++ -g -c student.cpp

clean:
	-rm *.o pex2