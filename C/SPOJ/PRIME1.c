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

// Main Function
void init(BSTree *tree);
void insert(BSTree *tree, int value);
BSTNode *createNode(int value);
void proses(BSTree tree, int *kiri, int *kanan);

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
/////////////////// proses data///////
    int *kiri, *kanan;
    kiri = (int*) calloc(tree.maxDepth - 1, sizeof(int) * tree.maxDepth - 1);
    kanan = (int*) calloc(tree.maxDepth - 1, sizeof(int) * tree.maxDepth - 1);

    proses(tree, kiri, kanan);
    
    printf("%d\n", tree.root->key);

    free(kiri);
    free(kanan);
    return 0;
}

void proses(BSTree tree, int *kiri, int *kanan) {
    BSTNode *currNode = tree.root;

    if (tree.maxDepth % 2 == 0)  // If genap
    {
        // kiri
        for (int i = tree.maxDepth - 1; i > 0; i--) {
            currNode = currNode->left->left;
            kiri[i] = currNode->key;
        }

        // kanan
        currNode = tree.root;
        for (int i = tree.maxDepth - 1; i > 0; i--) {
            currNode = currNode->right;
            kanan[i] = currNode->key;
            currNode = currNode->right;
        }

        for (int i = 0; i < tree.maxDepth; i++) {
            if (kiri[i] != 0) printf("%d ", kiri[i]);
            if (kanan[i] != 0) printf("%d ", kanan[i]);
        }
    }
    else // if ganjil
    {
        // kiri
        for (int i = tree.maxDepth - 1; i > 0; i--) {
            currNode = currNode->left;
            if (!currNode) break;
            kiri[i] = currNode->key;
            currNode = currNode->left;
        }

        // kanan
        currNode = tree.root;
        for (int i = tree.maxDepth - 1; i > 0; i--) {
            currNode = currNode->right->right;
            if (!currNode) break;
            kanan[i] = currNode->key;
        }

        for (int i = 0; i < tree.maxDepth; i++) {
            if (kiri[i] != 0) printf("%d ", kiri[i]);
            if (kanan[i + 1] != 0) printf("%d ", kanan[i + 1]);
        }
    }
}

BSTNode *_insert(BSTNode *root, int value) {
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

void insert(BSTree *tree, int value) {
    tree->root = _insert(tree->root, value);
    if (currNodeDepth > tree->maxDepth) {
        tree->maxDepth = currNodeDepth;
    }
}

BSTNode *createNode(int value) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void init(BSTree *tree) {
    tree->root = NULL;
    tree->maxDepth = 0;
}
