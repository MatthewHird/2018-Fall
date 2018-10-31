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
    struct Node {
        int numId[3];
        Student* student[3];
        int size;
        Node* child[4];
    };

    /**
     * @brief
     *
     * @param numberId
     *
     * @return
     */
    Node* search(int numberId);

    Node* root;
    std::string dataList;
};


#endif //ASSIGNMENT_2_TWO_FOUR_TREE_H
