//------------------------------------------------------------------------------
// @file    university_records.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "university_records.h"
#include <iostream>
#include "string_id_bst.h"
#include "two_four_tree.h"
#include "student.h"
#include "my_exceptions.h"
#include "menu_command.h"


UniversityRecords::UniversityRecords() {}


UniversityRecords::~UniversityRecords() {}


void UniversityRecords::run(std::string* arrayOfCsvFileNames) {

}


void UniversityRecords::menu() {

}


void UniversityRecords::displayMenuOptions() {

}


void UniversityRecords::loadCsvFile(std::string fileName) {

}


void UniversityRecords::saveAllToCsvFile(std::string fileName) {

}


void UniversityRecords::submitStudentInfo() {

}


void UniversityRecords::displayStudentInfo(Student& student) {

}


void UniversityRecords::listAllStudentNumber() {

}


void UniversityRecords::listAllStudentName() {

}


void UniversityRecords::quitProgram() {

}


std::string UniversityRecords::getStringInput(int maxLength) {
    return "";
}


MenuCommand* UniversityRecords::getCommand() {
    auto butt = new std::string[1];
    return new MenuCommand('i', 1, butt);
}


std::string UniversityRecords::getStudentNumber() {
    return "";
}


bool UniversityRecords::validateStudentNumber(int studentNumber) {
    return true;
}
