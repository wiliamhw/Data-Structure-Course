#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode {
    int key;
    bool killed;
    struct BSTNode *left, *right, *parent;
} BSTNode;

typedef struct BSTree {
    BSTNode *root;
    int maxDepth;
} BSTree;

int currNodeDepth;
bool stop = false;

// Main Function
void init(BSTree *tree);
void insert(BSTree *tree, int value);
BSTNode *createNode(int value);
void freeALL(BSTNode **root);
void getDeepestParent(BSTNode *root, int level, BSTNode **observer);
bool fight(int peluru, BSTNode *observer, int *queue);

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

    int kapasitas, mag, peluru;
    scanf("%d %d", &kapasitas, &mag);
    peluru = kapasitas + (kapasitas * mag);
    
    int *queue = malloc(sizeof(int) * peluru);
    if (!queue) return 1;
    memset(queue, 0, sizeof(queue));

    BSTNode *observer = NULL;
    getDeepestParent(tree.root, tree.maxDepth - 1, &observer);

    // 1 = menang, 0 kalah (retard)
    bool won = fight(peluru, observer, queue);

    if (won) {
        printf("A 200 IQ play.\n");
        printf("Kill:");

        for (int i = 0; i < peluru; i++) {
            if (queue[i] == 0) break;
            printf(" %d", queue[i]);
        }
    }
    else printf("Retard.");
    puts("");

    free(queue);
    freeALL(&tree.root);
    return 0;
}

bool fight(int peluru, BSTNode *observer, int *queue)
{
    for (int i = 0; i < peluru; i++)
    {
        if ((observer->left && observer->left->killed) || (observer->right && observer->right->killed)) {
            queue[i] = observer->key;
            observer->killed = true;

            if (observer->parent)
                observer = observer->parent;
            else return true;
        }

        else if (observer->left && !observer->left->killed) {
            queue[i] = observer->left->key;
            observer->left->killed = true;
        }
        else if (observer->right && !observer->right->killed) {
            queue[i] = observer->right->key;
            observer->right->killed = true;
        }
    }

    if (observer->left && !observer->left->killed)
        return false;
    else if (observer->right && !observer->right->killed)
        return false;
    else return true;
}

void getDeepestParent(BSTNode *root, int level, BSTNode **observer)
{
    if (!root || stop) return; 
    if (level == 0 && (root->left || root->right)) {
        *observer = root;
        stop = true;
    }
    else if (level > 0 && !stop) 
    { 
        getDeepestParent(root->left, level-1, observer); 
        getDeepestParent(root->right, level-1, observer); 
    } 
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
        root->left->parent = root;
    }

    else if (value > root->key) {
        root->right = _insert(root->right, value);
        root->right->parent = root;
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
    newNode->killed = false;
    newNode->left = newNode->right = newNode->parent = NULL;
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