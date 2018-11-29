//------------------------------------------------------------------------------
// @file    my_exceptions.h
// @author  Matthew Hird
// @date    November 28, 2018
//
// @brief   A set of custom exceptions for the program pex3. All exceptions
//          inherit from std::exception.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_3_MY_EXCEPTIONS_H
#define ASSIGNMENT_3_MY_EXCEPTIONS_H

#include <exception>
#include <string>


class InvalidUserName : public std::exception {
public:
    explicit InvalidUserName(std::string &invalidName) : name(invalidName){};

    const char* what() const noexcept override {
        return exception::what();
    }

    std::string getInvalidName() {
        return name;
    }
private:
    std::string name;
};


class InvalidDistance : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class InvalidEdgeToSelf : public std::exception {
public:
    explicit InvalidEdgeToSelf(std::string &invalidName) : name(invalidName){};

    const char* what() const noexcept override {
        return exception::what();
    }

    std::string getInvalidName() {
        return name;
    }
private:
    std::string name;
};


class InvalidPathToSelf : public std::exception {
public:
    explicit InvalidPathToSelf(std::string &invalidName) : name(invalidName){};

    const char* what() const noexcept override {
        return exception::what();
    }

    std::string getInvalidName() {
        return name;
    }
private:
    std::string name;
};


class SaveFileError : public std::exception {
public:
    const char* what() const noexcept override {
        return exception::what();
    }
};


class FailedToOpenSaveFile : public SaveFileError {
public:
    const char* what() const noexcept override {
        return SaveFileError::what();
    }
};


class InvalidSaveFileSyntax : public SaveFileError {
public:
    const char* what() const noexcept override {
        return SaveFileError::what();
    }
};

#endif //ASSIGNMENT_3_MY_EXCEPTIONS_H
