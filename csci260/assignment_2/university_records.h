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
#include "string_id_bst.h"
#include "two_four_tree.h"
#include "student.h"
#include "my_exceptions.h"
#include "menu_command.h"


class UniversityRecords {
public:
    /**
     * @brief
     */
    UniversityRecords();

    /**
     * @brief
     */
    ~UniversityRecords();

    /**
     * @brief
     *
     * @param arrayOfCsvFileNames
     */
    void run(std::string* arrayOfCsvFileNames);

private:
    /**
     * @brief
     */
    void menu();

    /**
     * @brief
     */
    void displayMenuOptions();

    /**
     * @brief
     *
     * @param fileName
     */
    void loadCsvFile(std::string fileName);

    /**
     * @brief
     *
     * @param fileName
     */
    void saveAllToCsvFile(std::string fileName);

    /**
     * @brief
     */
    void submitStudentInfo();

    /**
     * @brief
     *
     * @param student
     */
    void displayStudentInfo(Student &student);

    /**
     * @brief
     */
    void listAllStudentNumber();

    /**
     * @brief
     */
    void listAllStudentName();

    /**
     * @brief
     */
    void quitProgram();

    /**
     * @brief
     *
     * @param maxLength
     *
     * @return
     */
    std::string getStringInput(int maxLength=80);

    /**
     * @brief
     *
     * @return
     */
    MenuCommand* getCommand();

    /**
     * @brief
     *
     * @return
     */
    std::string getStudentNumber();

    /**
     * @brief
     *
     * @param studentNumber
     *
     * @return
     */
    bool validateStudentNumber(int studentNumber);

    const std::string CMD_PROMPT = ">>>  ";
    const std::string SUB_FIELD_PROMPT = "  >  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";

    TwoFourTree numberTree;
    StringIdBST nameTree;
};


#endif //ASSIGNMENT_2_UNIVERSITY_RECORDS_H
