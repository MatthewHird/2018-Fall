//------------------------------------------------------------------------------
// @file       my_exceptions.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
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
