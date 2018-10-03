//------------------------------------------------------------------------------
// @file    my_exceptions.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   A set of custom exceptions for the program pex1. All exceptions
//          inherit from std::exception.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_MY_EXCEPTIONS_H
#define ASSIGNMENT_1_MY_EXCEPTIONS_H

#include <exception>


class FullHeapException : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class EmptyHeapException : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidPriority : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidEstExecTime : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidSubmitterId : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidStartCommand : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidResourceList : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};

#endif //ASSIGNMENT_1_MY_EXCEPTIONS_H
