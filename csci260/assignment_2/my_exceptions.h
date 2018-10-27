//------------------------------------------------------------------------------
// @file    my_exceptions.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   A set of custom exceptions for the program pex2. All exceptions
//          inherit from std::exception.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_MY_EXCEPTIONS_H
#define ASSIGNMENT_1_MY_EXCEPTIONS_H

#include <exception>


class InvalidStudentNumber : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidStudentName : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidStreetAddress : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidCityAddress : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidEmailAddress : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};

#endif //ASSIGNMENT_1_MY_EXCEPTIONS_H
