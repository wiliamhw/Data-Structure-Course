/* Luzi Suka Berhitung
https://www.hackerrank.com/contests/sdd-m3/challenges/luzi-suka-berhitung
Input dan cari data dalam AVLTree
beserta urutannya dari yang terkecil
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
AVLNode* createNode(int value);
void insert(AVLTree *tree, int value);

// UTILITY FUNCTION
AVLNode *leftRotation(AVLNode *node);
AVLNode *rightRotation(AVLNode *node);
bool find(AVLNode *node, int value);
void inorder(AVLNode *node, int value);

// Helper Function
int Max(int a, int b);
AVLNode *_insert(AVLNode *node, int value);
void update(AVLNode *node);
AVLNode *balance(AVLNode *node);
AVLNode *leftLeftCase(AVLNode *node);
AVLNode *leftRightCase(AVLNode *node);
AVLNode *rightRightCase(AVLNode *node);
AVLNode *rightLeftCase(AVLNode *node);

long long int sum;
int urutan;
bool found;

int main(void) {
    AVLTree tree;
    init(&tree);

    int loop;
    scanf("%d", &loop);

    for (int i = 0; i < loop; i++) {
        int counter = 0;

        // Get command and value
        int opcode, val;
        scanf("%d %d", &opcode, &val);

        if (opcode == 1) { // Insert
            insert(&tree, val);
        }
        else { // opcode == 2, Search
            if (find(tree.root, val)) {
                sum = urutan = 0;
                found = false;
                inorder(tree.root, val);

                printf("Jumlahnya: %lld\n", sum);
                printf("Di urutan: %d\n", urutan);
            }
            else
                printf("Ga Ketemu :(\n");
        }
    }

    return 0;
}

bool find(AVLNode *node, int value) {
    while (node) {
        if (value < node->value) {
            node = node->left;
        }
        else {  
            if (value > node->value) node = node->right;
            else return true;
        }
    }
    return false;
}

void inorder(AVLNode *node, int value) {
    if (node && !found) {
        inorder(node->right, value); // Traverse to right corner

        if (found) return;
        sum += node->value; // Get traversed node's sum
        urutan++; // Get order from the biggest
        
        if (node->value == value) {
            found = true;
            return;
        }

        inorder(node->left, value); // Traverse to left
    }
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
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(AVLTree *tree, int value) {
    tree->root = _insert(tree->root, value);
    tree->size++;
}

AVLNode *_insert(AVLNode *node, int value) {
    if (!node) {
        return createNode(value);
    }
    else if (value < node->value) {
        node->left = _insert(node->left, value);
    }
    else if (value > node->value) {
        node->right = _insert(node->right, value);
    }

    update(node);
    return balance(node);
}

// UTILIYY FUNCTION

AVLNode *leftRotation(AVLNode *node) {
    AVLNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    update(node);
    update(newParent);
    return newParent;
}

AVLNode *rightRotation(AVLNode *node) {
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
