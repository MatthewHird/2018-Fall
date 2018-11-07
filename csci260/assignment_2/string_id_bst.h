//------------------------------------------------------------------------------
// @file    id_string_bst.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_STRING_ID_BST_H
#define ASSIGNMENT_2_STRING_ID_BST_H

#include <iostream>
#include "my_exceptions.h"


class StringIdBST {
public:
    /**
     * @brief
     */
    StringIdBST();

    /**
     * @brief
     */
    ~StringIdBST();

    /**
     * @brief
     *
     * @param stringId
     * @param intId
     */
    void insert(std::string stringId, int intId);

    /**
     * @brief
     *
     * @return
     */
    std::string& getAlphabeticalDataList();

    /**
     * @brief
     *
     * @return
     */
    bool isEmpty();
private:
    struct Node {
        std::string stringId;
        int intId;

        Node* left;
        Node* right;
    };

    /**
     * @brief
     *
     * @param node
     */
    void inorderListData(Node* node);

    /**
     * @brief
     *
     * @param node
     */
    void postOrderDestroyData(Node* node);

    Node* root;
    std::string* dataList;
    int size;
};


#endif //ASSIGNMENT_2_STRING_ID_BST_H
