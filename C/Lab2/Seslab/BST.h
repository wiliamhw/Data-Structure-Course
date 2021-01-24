/* BST tanpa elemen yg sama
https://github.com/AlproITS/StrukturData/blob/master/For%20C/Binary%20Search%20Tree/unique_binary_search_tree.c
*/
#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *left, *right;
} BSTNode;

typedef struct BSTree {
    BSTNode *root;
    unsigned int size;
} BSTree;

// Main Function
void init(BSTree *tree);
void insert(BSTree *tree, int value);
BSTNode *createNode(int value);
void preorder(BSTNode *root);
void inorder(BSTNode *root);
void postorder(BSTNode *root);
void delete(BSTree *tree, int value);
bool find(BSTNode *root, int value);
BSTNode *search(BSTNode *root, int value);
BSTNode *findMinNode(BSTNode *root);
void freeALL(BSTNode **root);

// Helper Function
BSTNode *_insert(BSTNode *root, int value);
BSTNode *_delete(BSTNode *root, int value);

#endif // BST_H