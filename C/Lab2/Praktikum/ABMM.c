#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *left, *right;
} BSTNode;

typedef struct BSTree {
    BSTNode *root;
    int maxDepth;
} BSTree;

int currNodeDepth;
bool min, once, last;

// Main Function
void init(BSTree *tree);
void insert(BSTree *tree, int value);
BSTNode *createNode(int value);
int *ambilMin(BSTNode root, int depth);
int *ambilMax(BSTNode root, int depth);
void reverseLevelOrder(BSTree tree);
void printGivenLevel(BSTNode *root, int level, int *max);
void freeALL(BSTNode **root);

// Helper Function
BSTNode *_insert(BSTNode *root, int value);

int main(void)
{
    BSTree tree;
    init(&tree);

    int banyak, input;
    scanf("%d", &banyak);

    while (banyak-- != 0)
    {
        scanf("%d", &input);
        currNodeDepth = 0;

        insert(&tree, input);
    }

    reverseLevelOrder(tree);

    freeALL(&tree.root);
    return 0;
}

void printGivenLevel(BSTNode *root, int level, int *max) 
{ 
    if (!root) return; 
    if (level == 0) {
        if (once && min) {
            printf("%d", root->key);
            once = false;
        }
        else { // max
            *max = root->key;
        }
    }
    else if (level > 0) 
    { 
        printGivenLevel(root->left, level-1, max); 
        printGivenLevel(root->right, level-1, max); 
    } 
} 

void reverseLevelOrder(BSTree tree) 
{
    int max;
    int j = 0;
    last = false;

    for (int i = tree.maxDepth; i >= 0; i--) {
        once = true;
        if (i == 0) last = true;

        if (j++ % 2 == 0) min = true;
        else min = false;

        printGivenLevel(tree.root, i, &max);

        if (!min) printf("%d", max);

        if (!last) printf(" ");
    }
    puts("");
} 

BSTNode *_insert(BSTNode *root, int value) 
{
    if (!root) {
        BSTNode *temp = createNode(value);
        return temp;
    }

    currNodeDepth++;
    if (value < root->key) {
        root->left = _insert(root->left, value);
    }

    else if (value > root->key) {
        root->right = _insert(root->right, value);
    }

    return root;
}

void insert(BSTree *tree, int value) 
{
    tree->root = _insert(tree->root, value);
    if (currNodeDepth > tree->maxDepth) {
        tree->maxDepth = currNodeDepth;
    }
}

BSTNode *createNode(int value) 
{
    BSTNode *newNode = malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void init(BSTree *tree) 
{
    tree->root = NULL;
    tree->maxDepth = 0;
}

void freeALL(BSTNode **root) {
    if (*root) {
        freeALL(&(*root)->left);
        freeALL(&(*root)->right);
        free(*root);
    }
}