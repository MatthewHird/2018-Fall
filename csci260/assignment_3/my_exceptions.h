//------------------------------------------------------------------------------
// @file    my_exceptions.h
// @author  Matthew Hird
// @date    November 18, 2018
//
// @brief   A set of custom exceptions for the program pex3. All exceptions
//          inherit from std::exception.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_3_MY_EXCEPTIONS_H
#define ASSIGNMENT_3_MY_EXCEPTIONS_H

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


class DuplicateKeyError: public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class EmptyTreeError: public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class KeyNotFoundError: public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class FullNodeError: public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};

class EmptyStack : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: Stack is empty\n";
    };
};

#endif //ASSIGNMENT_3_MY_EXCEPTIONS_H
