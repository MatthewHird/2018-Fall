//------------------------------------------------------------------------------
// @file    university_records.h
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

#ifndef ASSIGNMENT_2_UNIVERSITY_RECORDS_H
#define ASSIGNMENT_2_UNIVERSITY_RECORDS_H

#include <iostream>
#include "string_id_bst.h"
#include "two_four_tree.h"
#include "student.h"
#include "my_exceptions.h"


class UniversityRecords {
public:
    /**
     * @brief Default class constructor.
     */
    UniversityRecords()= default;

    /**
     * @brief Class destructor.
     */
    ~UniversityRecords()= default;

    /**
     * @brief Public entry point of the program. Takes user to main menu.
     */
    void run();

private:
    /**
     * @brief The control hub of the program.
     */
    void menu();

    /**
     * @brief Prints menu options to the screen.
     */
    void displayMenuOptions();

    /**
     * @brief Prompts user to input information for new student record.
     */
    void submitStudentInfo();

    /**
     * @brief Prompts user to input a student number, then displays all
     *        information in the student record of that student number.
     */
    void findStudentData();

    /**
     * @brief Prints student information to the screen.
     *
     * @param student   Student object whose information needs to be displayed.
     */
    void displayStudentInfo(Student &student);

    /**
     * @brief In ascending order of student numbers, displays the student number
     *        and name of every student in the system.
     */
    void listAllStudentNumber();

    /**
     * @brief In alphabetical order of student names, displays the student
     *        number and name of every student in the system.
     */
    void listAllStudentName();

    /**
     * @brief Abandons all information stored in the system (freeing up the
     *        memory) and exits the application.
     */
    void quitProgram();

    /**
     * @brief Prompts user to input string. Displays error message and reprompts
     *        user if entry exceeds maxLength.
     *
     * @param maxLength Maximum length of user input string.
     *
     * @return String entered by the user.
     */
    std::string getStringInput(int maxLength=80);

    /**
     * @brief Prompts user to input a command.
     *
     * @return The first character of the user's entry. Returns "" if user
     *         enters empty string.
     */
    std::string getCommand();

    /**
     * @brief Prompts user to enter 6 digit student number. Displays error
     *        message and reprompts user if entry is < 100000 or > 999999.
     *
     * @return  The student number entered by the user.
     */
    int getStudentNumber();

    const std::string CMD_PROMPT = ">>>  ";
    const std::string SUB_FIELD_PROMPT = "  >  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";

    TwoFourTree numberTree;
    StringIdBST nameTree;
};


#endif //ASSIGNMENT_2_UNIVERSITY_RECORDS_H
