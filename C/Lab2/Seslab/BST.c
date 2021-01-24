/* BST tanpa elemen yg sama
https://github.com/AlproITS/Strukturtree/blob/master/For%20C/Binary%20Search%20Tree/unique_binary_search_tree.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "BST.h"

void init(BSTree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

void insert(BSTree *tree, int value) {
    tree->root = _insert(tree->root, value);
    tree->size++;
}

BSTNode *_insert(BSTNode *root, int value) {
    if (!root) {
        BSTNode *temp = createNode(value);
        return temp;
    }

    else if (value < root->key) {
        root->left = _insert(root->left, value);
    }

    else if (value > root->key) {
        root->right = _insert(root->right, value);
    }

    return root;
}

BSTNode *createNode(int value) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(BSTNode *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void postorder(BSTNode *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

void delete(BSTree *tree, int value) {
    tree->root = _delete(tree->root, value);
    tree->size--;
}

BSTNode *_delete(BSTNode *root, int value) {
    if (!root) return NULL;

    if (value > root->key) {
        root->right = _delete(root->right, value);
    }
    else if (value < root->key) {
        root->left = _delete(root->right, value);
    }
    else {
        if (!root->left) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (!root->right) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = findMinNode(root->right);
        root->key = temp->key;
        root->right = _delete(root->right, temp->key);
    }
    return root;
}

bool find(BSTNode *root, int value) {
    BSTNode *temp = search(root, value);
    if (!temp) 
        return false;

    else if (temp->key == value) 
        return true;

    else return false;
}

BSTNode *search(BSTNode *root, int value) {
    while (root) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode *findMinNode(BSTNode *root) {
    BSTNode *currNode = root;
    while (currNode->left) {
        currNode = currNode->left;
    }

    return currNode;
}

void freeALL(BSTNode **root) {
    if (*root) {
        freeALL(&(*root)->left);
        freeALL(&(*root)->right);
        free(*root);
    }
}