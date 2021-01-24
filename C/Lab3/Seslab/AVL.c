#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "AVL.h"

// BASE FUNCTION
void init(AVLTree *tree) {
    tree->root = NULL;
    tree->size = 0u;
}

AVLNode *createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->value = value;
    newNode->height = newNode->BF = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(AVLTree *tree, int value) {
    if (find(tree->root, value)) return;

    tree->root = _insert(tree->root, value);
    tree->size++;
}

AVLNode *_insert(AVLNode* node, int value) {
    if (!node)
        return createNode(value);

    else if (value < node->value) {
        node->left = _insert(node->left, value);
    }

    else if (value > node->value) {
        node->right = _insert(node->right, value);
    }

    update(node);

    return balance(node);
}

// UTILITY FUNCTION
bool find(AVLNode *node, int value) {
    AVLNode *trav = node;

    while (trav) {
        if (value < trav->value)
            trav = trav->left;

        else if (value > trav->value)
            trav = trav->right;

        else
            return true;
    }
    return false;
}

int findMin(AVLNode *node) {
    while (node->left) {
        node = node->left;
    }
    return node->value;
}

int findMax(AVLNode *node) {
    while (node->right) {
        node = node->right;
    }
    return node->value;
}

void preorder(AVLNode *node) {
    if (node) {
        printf("%d ", node->value);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(AVLNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->value);
        inorder(node->right);
    }
}

void postorder(AVLNode *node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->value);
    }
}

AVLNode *leftRotation(AVLNode *node) {
    AVLNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;
    update(node);
    update(newParent);
    return newParent;
}

AVLNode *rightRotation(AVLNode* node) {
    AVLNode* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    update(node);
    update(newParent);
    return newParent;
}


// HELPER FUNCTION
int Max(int a, int b) {
    return (a > b)? a : b;
}

void update(AVLNode *node)  {
    int leftNodeHeight = (!node->left)? -1 : node->left->height;
    int rightNodeHeight = (!node->right)? -1 : node->right->height;

    node->height = 1 + Max(leftNodeHeight, rightNodeHeight);

    node->BF = rightNodeHeight - leftNodeHeight;
}

AVLNode *balance(AVLNode *node) {
    // Left heavy subtree
    if (node->BF == -2) {
        if (node->left->BF <= 0) { 
            return leftLeftCase(node);
        }
        else {
            return leftRightCase(node);
        }
    }
    // Right heavy subtree
    else if (node->BF == 2) {
        if (node->right->BF >= 0) {
            return rightRightCase(node);
        }
        else { 
            return rightLeftCase(node);
        }
    }
    // Node either has a balance factor of 0, +1 or -1 which is fine
    return node;
}

AVLNode *leftLeftCase(AVLNode *node) {
    return rightRotation(node);
}

AVLNode *leftRightCase(AVLNode *node) {
    node->left  = leftRotation(node->left);
    return leftLeftCase(node);
}

AVLNode *rightRightCase(AVLNode *node) {
    return leftRotation(node);
}

AVLNode *rightLeftCase(AVLNode *node) {
    node->right = rightRotation(node->right);
    return rightRightCase(node);
}

// Optional
void remove(AVLTree* tree, int value) {
    AVLNode* newRoot = _delete(tree->root, value);
    tree->size--;
}

AVLNode *_remove(AVLNode *node, int value) {
    if (!node) return NULL;

    // Search the node we wish to delete
    if (value < node->value) {
        node->left = _delete(node->left, value);
    }
    else if (value > node->value) {
        node->right = _delete(node->right, value);
    }

    // Found the node we wish to delete
    else {
        if (!node->left) {
            AVLNode* rightChild = node->right;
            free(node);
            return rightChild;
        }
        else if (!node->right) {
            AVLNode* leftChild = node->left;
            free(node);
            return leftChild;
        }

        // If there are two successor,
        // choose the one that will make the tree balanced
        else {

            // Choose to delete from left subtree
            if (node->left->height > node->right->height) {

                // Swap the value of the successor into the node
                int successorValue = findMax(node->left);
                node->value = successorValue;

                // Find the largest node in the left subtree
                AVLNode* replacement = _delete(node->left, successorValue);
                node->right = replacement;
            }
            else {
                // Swap the value of the successor into the node
                int successorValue = findMin(node->right);
                node->value = successorValue;

                // Find the smallest in the right subtree
                AVLNode* replacement = _delete(node->right, successorValue);
                node->right = replacement;
            }
        }
    }

    update(node);

    return balance(node);
}

void freeALL(AVLNode **root) {
    if (*root) {
        freeALL(&(*root)->left);
        freeALL(&(*root)->right);
        free(*root);
    }
}