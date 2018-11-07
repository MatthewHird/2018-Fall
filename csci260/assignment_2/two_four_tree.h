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
#include <utility>
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
     * @param key
     *
     * @return
     */
    TwoFourNode* search(int key);

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
     * @param key
     *
     * @return
     */
    int findKey(int key);

    /**
     * @brief
     *
     * @param key
     * @param newData
     */
    void insertNotFull(int key, Student& newData) throw(FullNodeError);

    /**
     * @brief
     *
     * @param index
     * @param oldChild
     */
    void splitChild(int index, TwoFourNode* oldChild);

    /**
     * @brief
     *
     * @param key
     */
    Student* remove(int key);

    /**
     * @brief
     *
     * @param index
     */
    Student* removeFromLeaf(int index);

    /**
     * @brief
     *
     * @param index
     */
    Student* removeFromNonLeaf(int index);

    /**
     * @brief
     *
     * @param index
     *
     * @return
     */
    int getPred(int index);

    /**
     * @brief
     *
     * @param index
     *
     * @return
     */
    int getSucc(int index);

    /**
     * @brief
     *
     * @param index
     */
    void fill(int index);

    /**
     * @brief
     *
     * @param index
     */
    void borrowFromPrev(int index);

    /**
     * @brief
     *
     * @param index
     */
    void borrowFromNext(int index);

    /**
     * @brief
     *
     * @param index
     */
    void merge(int index);

    friend class TwoFourTree;
private:
    static const int maxSize = 3;
    int keys[maxSize];
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
