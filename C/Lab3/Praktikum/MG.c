/* Maryo Gabut
https://www.hackerrank.com/contests/sdd-m3/challenges/maryo-gabut
Selisih parent dan sibling milik parent
*/

#include <stdio.h>
#include <stdlib.h>
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
void inorder(AVLNode *node);
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

// CUSTOM FUNCTION
AVLNode **findParent(AVLNode *node, int value);
int getSibling(AVLNode **parent);

int main(void) {

    AVLTree tree;
    init(&tree);

    // Get banyak data dan banyak case(T)
    int banyak, T, value;
    scanf("%d %d", &banyak, &T);

    // Get value
    while (banyak-- != 0) {
        scanf("%d", &value);
        insert(&tree, value);
    }

    // Get case
    while (T-- != 0) {
        scanf("%d", &value);

        // Variable to store parent (1) and its predecessor (0)
        AVLNode **parent = findParent(tree.root, value);

        // If parent is found
        if (parent[1]) {
            int pSibling = getSibling(parent);
            int selisih = abs(parent[1]->value - pSibling);
            printf("%d\n", selisih);
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}

int getSibling(AVLNode **parent) {
    int pSibling;

    // Check parent's sibling existence
    if (parent[0] && parent[0]->left && parent[0]->right) {

        // Check sibling position
        if (parent[0]->right == parent[1]) {
            pSibling = parent[0]->left->value; // Sibling is on the left
        }
        else {
            pSibling = parent[0]->right->value; // Sibling is on the right
        }
    }
    else {
        pSibling = 0;
    }
    return pSibling;
}

AVLNode **findParent(AVLNode *node, int value) {
    AVLNode *trav = node;
    AVLNode **parent = calloc(2, sizeof(AVLNode) * 2);

    while (trav) {
        if (value == trav->value) {
            return parent;
        }
        else {
            parent[0] = parent[1];
            parent[1] = trav;
            
            if (value < trav->value) {
                trav = trav->left;
            }
            else {
                trav = trav->right;
            }
        }
    }

    // If value doesn't exist in tree
    parent[0] = parent[1] = NULL;
    return parent;
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

void inorder(AVLNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->value);
        inorder(node->right);
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
