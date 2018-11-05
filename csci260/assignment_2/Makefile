pex2: main.o university_records.o string_id_bst.o two_four_tree.o student.o menu_command.o
	g++ main.o university_records.o string_id_bst.o two_four_tree.o student.o menu_command.o -o pex2

main.o: main.cpp university_records.h
	g++ -g -c main.cpp

university_records.o: university_records.cpp university_records.h string_id_bst.h two_four_tree.h student.h my_exceptions.h menu_command.h
	g++ -g -c university_records.cpp

string_id_bst.o: string_id_bst.cpp string_id_bst.h student.h
	g++ -g -c string_id_bst.cpp

two_four_tree.o: two_four_tree.cpp two_four_tree.h student.h
	g++ -g -c two_four_tree.cpp

student.o: student.cpp student.h my_exceptions.h
	g++ -g -c student.cpp

menu_command.o: menu_command.cpp menu_command.h
	g++ -g -c menu_command.cpp

clean:
	-rm *.o pex2