//------------------------------------------------------------------------------
// @file    student.cpp
// @author  Matthew Hird
// @date    October 23, 2018
//
// @brief   The Student data class holds the student record information for an
//          individual student. This includes a 6 digit student number that
//          should be used as a unique identifier for the student. Each member
//          variable must be set within its specified range or else the setter
//          function will throw an exception.
//------------------------------------------------------------------------------

#include "student.h"
#include "my_exceptions.h"


Student::Student()
    : Student(0, "", "", "", "")
{}


// testing
Student::Student(int studentNumber)
    : Student(studentNumber, std::to_string(studentNumber), "", "", "")
{}


Student::Student(int studentNumber, std::string studentName,
        std::string streetAddress, std::string cityAddress,
        std::string emailAddress) throw(InvalidStudentNumber,
                InvalidStudentName, InvalidStreetAddress,
                InvalidCityAddress, InvalidEmailAddress) {
    setStudentNumber(studentNumber);
    setStudentName(studentName);
    setStreetAddress(streetAddress);
    setCityAddress(cityAddress);
    setEmailAddress(emailAddress);
}


void Student::setStudentNumber(int studentNumber) throw(InvalidStudentNumber) {
    this->studentNumber = studentNumber;
}


void Student::setStudentName(std::string studentName) throw(InvalidStudentName) {
    this->studentName = studentName;
}


void Student::setStreetAddress(std::string streetAddress) throw(InvalidStreetAddress) {
    this->streetAddress = streetAddress;
}


void Student::setCityAddress(std::string cityAddress) throw(InvalidCityAddress) {
    this->cityAddress = cityAddress;
}


void Student::setEmailAddress(std::string emailAddress) throw(InvalidEmailAddress) {
    this->emailAddress = emailAddress;
}


int Student::getStudentNumber() {
    return studentNumber;
}


std::string Student::getStudentName() {
    return studentName;
}


std::string Student::getStreetAddress() {
    return streetAddress;
}


std::string Student::getCityAddress() {
    return cityAddress;
}


std::string Student::getEmailAddress() {
    return emailAddress;
}
