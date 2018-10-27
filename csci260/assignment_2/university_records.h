//------------------------------------------------------------------------------
// @file    university_records.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_UNIVERSITY_RECORDS_H
#define ASSIGNMENT_2_UNIVERSITY_RECORDS_H

#include <iostream>
#include "binary_search_tree.h"
#include "two_four_tree.h"
#include "student.h"
#include "my_exceptions.h"
#include "menu_command.h"

class UniversityRecords {
public:
    UniversityRecords();
    ~UniversityRecords();

    void run(std::string* arrayOfCsvFileNames);

private:

    void menu();

    void displayMenuOptions();

    void loadCsvFile(std::string fileName);

    void saveAllToCsvFile(std::string fileName);

    void submitStudentInfo();

    void displayStudentInfo(Student student);

    void listAllStudentNumber();

    void listAllStudentName();

    void quitProgram();

    std::string getStringInput(int maxLength=80);

    MenuCommand* getCommand();

    std::string getStudentNumber();

    bool validateStudentNumber(std::string studentNumber);

    const std::string CMD_PROMPT = ">>>  ";
    const std::string SUB_FIELD_PROMPT = "  >  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";

    TwoFourTree numberTree;
    BinarySearchTree nameTree;
};


#endif //ASSIGNMENT_2_UNIVERSITY_RECORDS_H
