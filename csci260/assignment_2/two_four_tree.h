//------------------------------------------------------------------------------
// @file    two_four_tree.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_TWO_FOUR_TREE_H
#define ASSIGNMENT_2_TWO_FOUR_TREE_H

#include <iostream>
#include "student.h"


class TwoFourNode {
public:
    friend class TwoFourTree;

private:
    static const int maxSize = 3;
    int key[maxSize];
    Student* data[maxSize];
    TwoFourNode* childPtr[maxSize + 1];
    bool isLeaf;
    int size;
};


class TwoFourTree {
public:
    /**
     * @brief
     */
    TwoFourTree();

    /**
     * @brief
     */
    ~TwoFourTree();

    /**
     * @brief
     *
     * @param numberId
     *
     * @return
     */
    Student& lookup(int numberId);

    /**
     * @brief
     *
     * @param studentInfo
     * @param student
     */
    void insert(int numberId, Student& studentInfo);

    /**
     * @brief
     *
     * @param numberId
     *
     * @return
     */
    Student& remove(int numberId);
private:


    /**
     * @brief
     *
     * @param numberId
     *
     * @return
     */
    TwoFourNode* search(int numberId);

    TwoFourNode* root;
    std::string dataList;
};




#endif //ASSIGNMENT_2_TWO_FOUR_TREE_H
