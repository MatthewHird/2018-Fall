//------------------------------------------------------------------------------
// @file    id_string_bst.h
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   A binary search tree that uses non-unique strings as keys, and
//          stores the key with an integer ID. getAlphabeticalDataList() does an
//          inorder traversal, returning a string containing the stringId key
//          and intId at each node.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_STRING_ID_BST_H
#define ASSIGNMENT_2_STRING_ID_BST_H

#include <iostream>
#include "my_exceptions.h"


class StringIdBST {
public:
    /**
     * @brief Default Class Constructor
     */
    StringIdBST();

    /**
     * @brief Class Destructor
     */
    ~StringIdBST();

    /**
     * @brief Inserts the stringId/intId pair into the tree alphabetically based
     *        on the stringId (ignoring character case, non-alphabetic
     *        characters (not within a to z), and spaces).
     *
     * @param stringId  The non-unique string that is used as the key.
     * @param intId     The integer paired with stringId.
     */
    void insert(std::string stringId, int intId);

    /**
     * @brief Generates a list of all stringId/intId pairs in alphabetical order
     *        (ignoring character case, non-alphabetic characters (not within
     *        a to z), and spaces) of the stringId of each pair. stringId's with
     *        the same alphabetical priority will be listed in the order they
     *        were inserted.
     *
     * @return  Entries are separated by '\n' character. The first entry is a
     *          positive integer stating the number of stringId/intId pairs in
     *          the list. Each pair is spread across 2 lines, with the first
     *          line containing the stringId, and the second line containing the
     *          intId. This means the string will contain (# of pairs) * 2 + 1
     *          entries.
     */
    std::string& getAlphabeticalDataList();

    /**
     * @brief Check if tree is empty.
     *
     * @return  true of tree is empty; false otherwise.
     */
    bool isEmpty();
private:
    struct Node {
        std::string keyString;
        std::string dataString;
        int dataInt;

        Node* left;
        Node* right;
    };

    /**
     * @brief Takes a string and returns a copy that has been converted to
     *        lowercase and had all non-alphabetic characters removed.
     *
     * @param dataString    String used to generate key string.
     *
     * @return  Copy of input string, converted to all lowercase, with all
     *          characters that match the pattern "[^a-z]" being removed.
     */
    std::string generateKeyString(std::string dataString);

    /**
     * @brief Recursive inorder traversal function. Upon visiting a node, it
     *        will append the dataString and dataInt to the next two lines of
     *        dataList (in the order=> newline dataString newline dataInt).
     *        WARNING: dataList must be pointing at a string object
     *        (not == nullptr).
     *
     * @param node  Node being visited.
     */
    void inorderListData(Node* node);

    /**
     * @brief Recursive postorder traversal function. Upon visiting a node, the
     *        node will be deleted.
     *
     * @param node  Node being visited.
     */
    void postOrderDestroyData(Node* node);

    Node* root;
    std::string* dataList;
    int size;
};


#endif //ASSIGNMENT_2_STRING_ID_BST_H
