//------------------------------------------------------------------------------
// @file    university_records.cpp
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   A program that stores student records for a university. Allows user 
//          to input student record data and add it to the system, display the 
//          record of a specific student number, or list the names and student 
//          numbers of all students in the system, either in ascending order of 
//          the student numbers, or alphabetically based on student name. When
//          the program terminates, all stored data is destroyed.
//------------------------------------------------------------------------------

#include "university_records.h"
#include <iostream>
#include "string_id_bst.h"
#include "two_four_tree.h"
#include "student.h"
#include "my_exceptions.h"
#include <math.h>
#include <algorithm>
#include <sstream>


void UniversityRecords::run() {
    menu();
}


void UniversityRecords::menu() {
    std::cout << "\n**** Welcome to the University Records System ****\n\n";

    displayMenuOptions();
    bool terminate = false;
    while (!terminate) {
        bool redisplayMenu = true;

        std::string command = getCommand();

        if (command == "i") {
            submitStudentInfo();
        } else if (command == "n") {
            findStudentData();
        } else if (command == "l") {
            listAllStudentNumber();
        } else if (command == "p") {
            listAllStudentName();
        } else if (command == "q") {
            quitProgram();
            terminate = true;
            redisplayMenu = false;
        } else {
            std::cout << "Invalid command: please try again\n";
            redisplayMenu = false;
        }

        if (redisplayMenu) {
            displayMenuOptions();
        }
    }
}


void UniversityRecords::displayMenuOptions() {
    std::cout << "Please enter one of the following commands:\n\n"
              << "i: Submit information for a new student and store the student\n"
              << "   record in the system.\n"
              << "n: Enter a student number to display all information on that student.\n"
              << "l: In ascending order of their student number, list the student number\n"
              << "   and name of all students in the system.\n"
              << "p: In the alphabetical order of the student names, list the name\n"
              << "   and student number of all students in the system.\n"
              << "q: Abandon all information stored in the system and exit the application.\n\n";
}


void UniversityRecords::submitStudentInfo() {
    std::cout << "Please input the six digit student number of new student\n";
    int studentNumber = getStudentNumber();
    std::cout << "Please input the name of the student in the form: 'Lastname, Firstname I.'\n";
    std::string studentName = getStringInput();
    std::cout << "Please input the address of the student (street number and street name)\n";
    std::string streetAddress = getStringInput();
    std::cout << "Please input the city the student lives in\n";
    std::string cityAddress = getStringInput();
    std::cout << "Please input the email address of the student\n";
    std::string emailAddress = getStringInput();

    Student* student;
    try {
        student = new Student(studentNumber, studentName, streetAddress, cityAddress, emailAddress);
    } catch (std::exception& e) {
        std::cout << "Error: Invalid student information\n";
        return;
    }

    try {
        numberTree.insert(student->getStudentNumber(), *student);
        nameTree.insert(studentName, studentNumber);
    } catch (DuplicateKeyError& e) {
        std::cout << "Error: A student record already exists using student number "
                  << student->getStudentNumber() << "\n" << LINE_BREAK;
        delete student;
        return;
    }

    std::cout << "Successfully added record for student number " << student->getStudentNumber() << "\n" << LINE_BREAK;
}


void UniversityRecords::findStudentData() {
    if (nameTree.isEmpty()) {
        std::cout << "Error: No student records found in system\n" << LINE_BREAK;
        return;
    }
    Student student;
    std::cout << "Please enter the student number of the student record you would like to view:\n";
    int key = getStudentNumber();
    try {
        student = numberTree.lookup(key);
        displayStudentInfo(student);
    } catch (EmptyTreeError& e) {
        std::cout << "Error: No student records found in system\n" << LINE_BREAK;
    } catch (KeyNotFoundError& e) {
        std::cout << "Error: Student number " << key << " is not in the system\n" << LINE_BREAK;
    }
}


void UniversityRecords::displayStudentInfo(Student& student) {
    std::cout << LINE_BREAK
              << "*** Student Record of " << student.getStudentName() << " ***\n\n"
              << "Student Number: " << student.getStudentNumber() << "\n"
              << "Student Name:   " << student.getStudentName() << "\n"
              << "Address:        " << student.getStreetAddress() << "\n"
              << "City:           " << student.getCityAddress() << "\n"
              << "Email Address:  " << student.getEmailAddress() << "\n\n"
              << LINE_BREAK;
}


void UniversityRecords::listAllStudentNumber() {
    std::stringstream listStream(numberTree.getKeyDataList());
    int dataPairCount;
    listStream >> dataPairCount;
    listStream.ignore();

    if (dataPairCount == 0) {
        std::cout << "Error: No student records found in system\n" << LINE_BREAK;
        return;
    }

    std::cout << LINE_BREAK
              << "Listing student numbers in ascending order:\n\n"
              << " Student#    Student Name\n\n";


    for (int i = 0; i < dataPairCount; i++) {
        std::string number;
        std::string name;
        std::getline(listStream, number);
        std::getline(listStream, name);
        std::cout << "  " << number << "      " << name << "\n";
    }
    std::cout << "\n" << LINE_BREAK;
}


void UniversityRecords::listAllStudentName() {
    std::stringstream listStream(nameTree.getAlphabeticalDataList());
    int dataPairCount;
    listStream >> dataPairCount;
    listStream.ignore();

    if (dataPairCount == 0) {
        std::cout << "Error: No student records found in system\n" << LINE_BREAK;
        return;
    }

    std::cout << LINE_BREAK
              << "Listing student names in alphabetical order:\n\n"
              << " Student#    Student Name\n\n";


    for (int i = 0; i < dataPairCount; i++) {
        std::string number;
        std::string name;
        std::getline(listStream, name);
        std::getline(listStream, number);
        std::cout << "  " << number << "      " << name << "\n";
    }
    std::cout << "\n" << LINE_BREAK;
}


void UniversityRecords::quitProgram() {
    std::cout << LINE_BREAK << "Thank-you for using the University Records System\n" << LINE_BREAK;
}


std::string UniversityRecords::getStringInput(int maxLength) {
    bool badInput;
    std::string line;

    do {
        badInput = false;
        std::cout << SUB_FIELD_PROMPT;
        std::getline(std::cin, line);
        std::cout << "\n";

        if (maxLength > 0) {
            if (line.length() > maxLength) {
                badInput = true;
                std::cout << "Input must be " << maxLength << " characters or less\n";
            }
        }
    } while (badInput == true);
    return line;
}


std::string UniversityRecords::getCommand() {
    std::string line;
    std::string command;

    std::cout << CMD_PROMPT;
    std::getline(std::cin, line);
    std::cout << "\n";

    std::transform(line.begin(), line.end(), line.begin(), tolower);
    if (line.empty()) {
        return line;
    }
    command += line.at(0);
    return command;
}


int UniversityRecords::getStudentNumber() {
    int num;
    bool badInput;

    do {
        badInput = false;
        std::cout << SUB_FIELD_PROMPT;

        if (!(std::cin >> num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            badInput = true;
            std::cout << "\nStudent number must be an integer in the range of 100000 to 999999\n";
        } else {
            if (num < 100000 || num > 999999) {
                badInput = true;
                std::cout << "\nStudent number must be an integer in the range of 100000 to 999999\n";
            } else {
                std::cout << "\n";
            }
            std::cin.ignore();
        }
    } while (badInput == true);
    return num;
}
