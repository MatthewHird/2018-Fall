//------------------------------------------------------------------------------
// @file    two_four_tree.h
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   A specialized two-four tree that stores (int key)/(Student data)
//          pairs. getKeyDataList() does an inorder traversal, returning a
//          string containing the studentNumber and studentName of every Student
//          object stored in the tree. lookup() searches the tree for the
//          specified key, and returns the associated Student object.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_TWO_FOUR_TREE_H
#define ASSIGNMENT_2_TWO_FOUR_TREE_H

#include <iostream>
#include <utility>
#include "student.h"


class TwoFourNode {
public:
    /**
     * @brief   Default class constructor. Default: isLeaf = false
     */
    TwoFourNode();

    /**
     * @brief Parameterized class constructor.
     *
     * @param isLeaf    Used to set isLeaf member variable. True if node is a
     *                  leaf node; false if node is an internal node.
     */
    explicit TwoFourNode(bool isLeaf);

    /**
     * @brief Class destructor. WARNING: Destroys stored studentData.
     */
    ~TwoFourNode();

    /**
     * @brief Recursive search function. Finds the node in the subtree that
     *        contains the specified key.
     *
     * @param key   The key being searched for.
     *
     * @return  The node containing the key. Returns nullptr if key is not
     *          found in the subtree.
     */
    TwoFourNode* search(int key);

    /**
     * @brief Recursive inorder traversal function. Upon visiting a
     *        key/studentData pair in the node, it will append the studentNumber
     *        and studentName from the studentData to the next two lines of the
     *        specified dataList (in the order=> newline studentNumber newline
     *        studentName). WARNING: dataList must be pointing at a string
     *        object (not == nullptr).
     *
     * @param dataList  The string being appended
     */
    void inorderListData(std::string* dataList);

    /**
     * @brief Recursive postorder traversal function. Upon being visited, the
     *        node will delete itself. When a node is deleted, all studentData
     *        stored in the node is deleted.
     */
    void postorderDestroyData();

    /**
     * @brief Finds the index of the smallest key value in this node that is
     *        greater than or equal to the specified key. Caller needs to check
     *        whether key is at keys[index] or key is in subtree at
     *        childPtr[index].
     *
     * @param key   Key being searched for.
     *
     * @return  0 if specified key is smaller than all keys in the node;
     */
    int findKey(int key);

    /**
     * @brief Recursive function that tries to insert key/studentData pair into
     *        a non-full node in the subtree. This node must not be full to use
     *        this function. If this is an internal node, all full nodes in the
     *        branch that the pair will be inserted into in the subtree will be
     *        split.
     *
     * @param key           Unique identifier of the key/value pair.
     * @param studentData   Student information to be stored in tree.
     *
     * @throws FullNodeError    if size == maxSize.
     */
    void insertNotFull(int key, Student& studentData) throw(FullNodeError);

    /**
     * @brief Splits specified (full) child node into two child nodes. Each
     *        child node gets 1 of the 3 key/data pairs and 2 of the 4 child
     *        pointers, while the parent (this node) gets the middle key/data
     *        pair.
     *
     * @param index The index of childPtr of the child to be split.
     */
    void splitChild(int index);

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
     * @brief Default class constructor.
     */
    TwoFourTree();

    /**
     * @brief Class destructor.
     */
    ~TwoFourTree();

    /**
     * @brief Inserts key/studentData pair into the tree based on unique key.
     *
     * @param key           Unique identifier of key/data pair.
     * @param studentData   Student information to be stored in the tree.
     *
     * @throws DuplicateKeyError    if key value is already used by another pair
     *                              in the tree.
     */
    void insert(int key, Student& studentData) throw(DuplicateKeyError);

    /**
     * @brief Searches tree for key and returns paired studentData.
     *
     * @param key   The unique identifier used to find paired studentData.
     *
     * @throws EmptyTreeError   if tree contains no key/data pairs.
     * @throws KeyNotFoundError if no pair in the tree uses the value key.
     *
     * @return  The studentData stored with key.
     */
    Student& lookup(int key) throw(EmptyTreeError, KeyNotFoundError);


    /**
     * @brief Generates a list of studentNumber/studentName pairs, in ascending
     *        order of studentNumber, from all studentData objects in the tree.
     *
     * @return  Entries are separated by '\n' character. The first entry is a
     *          positive integer stating the number of studentNumber/studentName
     *          pairs in the list. Each pair is spread across 2 lines, with the
     *          first line containing the studentNumber, and the second line
     *          containing the studentName. This means the string will contain
     *          (# of pairs) * 2 + 1 entries.
     */
    std::string& getKeyDataList();
private:
    TwoFourNode* root;
    std::string* dataList;
    int keyCount;
};


#endif //ASSIGNMENT_2_TWO_FOUR_TREE_H
