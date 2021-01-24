#include <stdbool.h>

typedef struct AVLNode {
    int value, height, BF;
    struct AVLNode *left, *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
    unsigned int size;
} AVLTree;

// BASE FUNCTION
void init(AVLTree *tree);
AVLNode *createNode(int value);
void insert(AVLTree *tree, int value);

// UTILITY FUNCTION
bool find(AVLNode *node, int value);
int findMin(AVLNode *node);
int findMax(AVLNode *node);
void preorder(AVLNode *node);
void inorder(AVLNode *node);
void postorder(AVLNode *node);
AVLNode *leftRotation(AVLNode *node);
AVLNode *rightRotation(AVLNode *node);


// HELPER FUNCTION
int Max(int a, int b);
AVLNode *_insert(AVLNode *node, int value);
void update(AVLNode *node);
AVLNode *balance(AVLNode *node);
AVLNode *leftLeftCase(AVLNode *node);
AVLNode *leftRightCase(AVLNode *node);
AVLNode *rightRightCase(AVLNode *node);
AVLNode *rightLeftCase(AVLNode *node);

// Optional
AVLNode *_remove(AVLNode *node, int value);
void remove(AVLTree *tree, int value);
void freeALL(AVLNode **root);
