//------------------------------------------------------------------------------
// @file    two_four_tree.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "two_four_tree.h"
#include <iostream>
#include "student.h"


TwoFourTree::TwoFourTree() {}


TwoFourTree::~TwoFourTree() {}


Student& TwoFourTree::lookup(int numberId) {
    Student* stud1 = new Student;
    return *stud1;
}


void TwoFourTree::insert(int numberId, Student &studentInfo) {

}


Student& TwoFourTree::remove(int numberId) {
    Student* stud1 = new Student;
    return *stud1;
}


TwoFourNode* TwoFourTree::search(int numberId) {
    TwoFourNode* node = new TwoFourNode;
    return node;
}
