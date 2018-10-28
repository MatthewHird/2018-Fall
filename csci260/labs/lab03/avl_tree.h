//
// Created by hirdm on 11/10/18.
//

#ifndef LAB03_AVL_TREE_H
#define LAB03_AVL_TREE_H


class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    void insert(int k);
private:
    struct TreeNode {
        int data;
        TreeNode *left;
        TreeNode *right;
        int balance;
    };

    TreeNode *root;
};


#endif //LAB03_AVL_TREE_H
