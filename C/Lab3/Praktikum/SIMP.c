/* Simp
https://www.hackerrank.com/contests/sdd-m3/challenges/simp
Taruh dan cari data di AVLTree
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLNode {
    int value, height, BF; 
    int leftSize, rightSize;
    struct AVLNode *left, *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
    unsigned int size;
} AVLTree;

// BASE FUNCTION
void init(AVLTree *tree);
AVLNode* createNode(int value);
void insert(AVLTree *tree, int value);

// UTILITY FUNCTION
AVLNode *leftRotation(AVLNode *node);
AVLNode *rightRotation(AVLNode *node);
bool find(AVLNode *node, int value, int *counter);
void inorder(AVLNode *node);

// Helper Function
int Max(int a, int b);
AVLNode *_insert(AVLNode *node, int value);
void update(AVLNode *node);
AVLNode *balance(AVLNode *node);
AVLNode *leftLeftCase(AVLNode *node);
AVLNode *leftRightCase(AVLNode *node);
AVLNode *rightRightCase(AVLNode *node);
AVLNode *rightLeftCase(AVLNode *node);
int bandingin(char cmd[20]);

int main(void) {
    AVLTree tree;
    init(&tree);

    int loop, val, counter;
    char cmd[20];
    scanf("%d", &loop);

    // Get command and value
    while (loop-- > 0) {
        counter = 0;
        scanf("%s %d", cmd, &val);

        // Get simplified command
        int opcode = bandingin(cmd);

        if (opcode == 0) { // Invalid input
            printf("AKU TUH GATAU HARUS NGAPAIN!\n");
        }
        else if (opcode == 1) { // Insert
            insert(&tree, val);
        }
        else { // opcode == 2, Search
            if (find(tree.root, val, &counter))
                printf("Kasetnya ada di tumpukan ke-%d\n", counter);
            else
                printf("Kasetnya gak ada!\n");
        }
    }

    return 0;
}

int bandingin(char cmd[20]) {
    if (strcmp("Taro", cmd) == 0) {
        return 1;
    }
    else if (strcmp("Cari", cmd) == 0) {
        return 2;
    }
    else return 0;
}

// BASE FUNCTION
void init(AVLTree *tree) {
    tree->root = NULL;
    tree->size = 0u;
}

AVLNode *createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->value = value;
    newNode->height = newNode->BF = 0;
    newNode->leftSize = newNode->rightSize = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(AVLTree *tree, int value) {
    tree->root = _insert(tree->root, value);
    tree->size++;
}

AVLNode *_insert(AVLNode *node, int value) {
    if (!node)
        return createNode(value);

    else if (value < node->value) {
        node->leftSize++;
        node->left = _insert(node->left, value);
    }

    else if (value > node->value) {
        node->rightSize++;
        node->right = _insert(node->right, value);
    }

    update(node);
    return balance(node);
}

// UTILIYY FUNCTION
void inorder(AVLNode *node) {
    if (node) {
        inorder(node->left);
        printf("Value:%d, Left:%d, Right:%d\n", node->value, node->leftSize, node->rightSize);
        inorder(node->right);
    }
}

bool find(AVLNode *node, int value, int *counter) {
    while (node) {
        if (value < node->value) 
            node = node->left;
        else { // value >= node->value
            *counter += node->leftSize + 1;
            
            if (value > node->value) node = node->right;
            else return true;
        }
    }
    return false;
}

AVLNode *leftRotation(AVLNode *node) {
    AVLNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    node->rightSize = (!node->right)? 0 : node->right->rightSize + node->right->leftSize + 1;
    newParent->leftSize = (!node)? 0 : node->leftSize + node->rightSize + 1;

    update(node);
    update(newParent);
    return newParent;
}

AVLNode *rightRotation(AVLNode *node) {
    AVLNode* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    node->leftSize = (!node->left)? 0 : node->left->leftSize + node->left->rightSize + 1;
    newParent->rightSize = (!node)? 0 : node->rightSize + node->leftSize + 1;

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
        if (node->left->BF <= 0) 
            return leftLeftCase(node);
        else 
            return leftRightCase(node);
    }
    // Right heavy subtree
    else if (node->BF == 2) {
        if (node->right->BF >= 0)
            return rightRightCase(node);
        else
            return rightLeftCase(node);
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
