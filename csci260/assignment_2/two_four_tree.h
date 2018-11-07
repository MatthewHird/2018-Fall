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
    /**
     * @brief
     */
    TwoFourNode();

    /**
     * @brief
     *
     * @param isLeaf
     */
    explicit TwoFourNode(bool isLeaf);

    /**
     * @brief
     */
    ~TwoFourNode();


    /**
     * @brief
     *
     * @param k
     *
     * @return
     */
    TwoFourNode* search(int k);

    /**
     * @brief
     */
    void inorderListData(std::string* dataList);

    /**
     * @brief
     */
    void postorderDestroyData();

    /**
     * @brief
     *
     * @param k
     *
     * @return
     */
    int findKey(int k);

    /**
     * @brief
     *
     * @param k
     * @param newData
     */
    void insertNotFull(int k, Student& newData) throw(FullNodeError);

    /**
     * @brief
     *
     * @param i
     * @param y
     */
    void splitChild(int i, TwoFourNode* y);

    /**
     * @brief
     *
     * @param k
     */
    Student* remove(int k);

    /**
     * @brief
     *
     * @param idx
     */
    Student* removeFromLeaf(int idx);

    /**
     * @brief
     *
     * @param idx
     */
    Student* removeFromNonLeaf(int idx);

    /**
     * @brief
     *
     * @param idx
     *
     * @return
     */
    int getPred(int idx);

    /**
     * @brief
     *
     * @param idx
     *
     * @return
     */
    int getSucc(int idx);

    /**
     * @brief
     *
     * @param idx
     */
    void fill(int idx);

    /**
     * @brief
     *
     * @param idx
     */
    void borrowFromPrev(int idx);

    /**
     * @brief
     *
     * @param idx
     */
    void borrowFromNext(int idx);

    /**
     * @brief
     *
     * @param idx
     */
    void merge(int idx);

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
    Student& lookup(int numberId) throw(EmptyTreeError, KeyNotFoundError);

    /**
     * @brief
     *
     * @param studentInfo
     * @param student
     */
    void insert(int numberId, Student& studentInfo) throw(DuplicateKeyError);

    /**
     * @brief
     *
     * @param numberId
     *
     * @return
     */
    Student& remove(int numberId) throw(EmptyTreeError, KeyNotFoundError);

    /**
     * @brief
     *
     * @return
     */
    std::string& getKeyDataList();
private:
    TwoFourNode* root;
    std::string* dataList;
    int size;
};


#endif //ASSIGNMENT_2_TWO_FOUR_TREE_H
