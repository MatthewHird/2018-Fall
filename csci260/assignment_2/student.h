//------------------------------------------------------------------------------
// @file    student.h
// @author  Matthew Hird
// @date    October 23, 2018
//
// @brief   The Student data class holds the student record information for an
//          individual student. This includes a 6 digit student number that
//          should be used as a unique identifier for the student. Each member
//          variable must be set within its specified range or else the setter
//          function will throw an exception.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_STUDENT_H
#define ASSIGNMENT_2_STUDENT_H

#include <iostream>
#include "my_exceptions.h"


class Student {
public:
    /**
     * @brief Default class constructor. studentNumber = "999999";
     *        studentName, streetAddress, cityAddress, emailAddress = "".
     */
    Student();


    /**
     * @brief Parameterized constructor.
     *
     * @param studentNumber 6 digit number to uniquely identify the student.
     * @param studentName   Name of the student (non-unique identifier) in the
     *                      form "Surname, Given Names".
     * @param streetAddress House number and street name of the student's
     *                      address.
     * @param cityAddress   City name of the student's address.
     * @param emailAddress  Student's email address.
     *
     * @throws InvalidStudentNumber if value > 999999 or value < 100000.
     * @throws InvalidStudentName   if length > 80 characters.
     * @throws InvalidStreetAddress if length > 80 characters.
     * @throws InvalidCityAddress   if length > 80 characters.
     * @throws InvalidEmailAddress  if length > 80 characters.
     */
    Student(int studentNumber, std::string studentName,
            std::string streetAddress, std::string cityAddress,
            std::string emailAddress) throw(InvalidStudentNumber,
                    InvalidStudentName, InvalidStreetAddress,
                    InvalidCityAddress, InvalidEmailAddress);

    /**
     * @brief Class destructor.
     */
    ~Student()= default;

    /**
     * @brief Sets the student number member variable.
     *
     * @param studentNumber 6 digit number to uniquely identify the student.
     *
     * @throws InvalidStudentNumber if value > 999999 or value < 100000.
     */
    void setStudentNumber(int studentNumber) throw(InvalidStudentNumber);

    /**
     * @brief Sets the student name member variable.
     *
     * @param studentName   Name of the student (non-unique identifier) in the
     *                      form "Surname, Given Names".
     *
     * @throws InvalidStudentName   if length > 80 characters.
     */
    void setStudentName(std::string studentName) throw(InvalidStudentName);

    /**
     * @brief Sets the street address member variable.
     *
     * @param streetAddress House number and street name of the student's
     *                      address.
     *
     * @throws InvalidStreetAddress if length > 80 characters.
     */
    void setStreetAddress(std::string streetAddress) throw(InvalidStreetAddress);

    /**
     * @brief Set the city address member variable.
     *
     * @param cityAddress   City name of the student's address.
     *
     * @throws InvalidCityAddress   if length > 80 characters.
     */
    void setCityAddress(std::string cityAddress) throw(InvalidCityAddress);

    /**
     * @brief Set the email address member variable.
     *
     * @param emailAddress  Student's email address.
     *
     * @throws InvalidEmailAddress  if length > 80 characters.
     */
    void setEmailAddress(std::string emailAddress) throw(InvalidEmailAddress);

    /**
     * @return  The value of the studentNumber member variable.
     */
    int getStudentNumber();

    /**
     * @return  The value of the studentName member variable.
     */
    std::string getStudentName();

    /**
     * @return  The value of the streetAddress member variable.
     */
    std::string getStreetAddress();

    /**
     * @return  The value of the cityAddress member variable.
     */
    std::string getCityAddress();

    /**
     * @return  The value of the emailAddress member variable.
     */
    std::string getEmailAddress();

private:
    int studentNumber;
    std::string studentName;
    std::string streetAddress;
    std::string cityAddress;
    std::string emailAddress;
};


#endif //ASSIGNMENT_2_STUDENT_H