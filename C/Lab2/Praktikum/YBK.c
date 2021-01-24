#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
typedef struct BSTNode {
    float key;
    struct BSTNode *left, *right;
} BSTNode;
 
typedef struct BSTree {
    BSTNode *root;
    int maxDepth;
} BSTree;

typedef struct node {
    float x;
    struct node *next;
} queue;

int currNodeDepth;
 
// Main Function
void init(BSTree *tree);
void insert(BSTree *tree, float value);
BSTNode *createNode(float value);
// void scanLevelOrder(BSTNode *root, int banyak);
void scanLevelOrder(BSTree tree);
void scanGivenLevel(BSTNode *root, int level, float *sum, int *banyak);
void freeALL(BSTNode **root);
 
// Helper Function
BSTNode *_insert(BSTNode *root, float value);
 
int main(void)
{
    BSTree tree;
 
    int tesCase;
    scanf("%d", &tesCase);
 
    while (tesCase-- != 0)
    {
        init(&tree);
 
        int banyak;
        float input;
        scanf("%d", &banyak);
 
        for (int i = 0; i < banyak; i++)
        {
            scanf("%f", &input);
            currNodeDepth = 0;
 
            insert(&tree, input);
        }
 
        scanLevelOrder(tree);
        freeALL(&tree.root);
        puts("");
    }
 
    return 0;
}

// void scanLevelOrder(BSTNode *root, int banyak)
// {
//     int rear = 0;
//     int front = 0;
//     BSTNode **queue = malloc(sizeof(BSTNode) * banyak);
//     BSTNode *temp = root;

//     while (temp)
//     {
//         printf("%.2f ", temp->key);

//         if (temp->left)
//             queue[rear++] = temp->left;
//         if (temp->right)
//             queue[rear++] = temp->right;

//         temp = queue[front++];
//     }
// }

void scanGivenLevel(BSTNode *root, int level, float *sum, int *banyak) 
{ 
    if (!root) return; 
    if (level == 0) {
        // printf("%.2f ", root->key);
        *sum += root->key;
        *banyak += 1;
    }
    else if (level > 0) 
    { 
        scanGivenLevel(root->left, level-1, sum, banyak); 
        scanGivenLevel(root->right, level-1, sum, banyak); 
    } 
} 
 
void scanLevelOrder(BSTree tree) 
{
    float sum;
    int banyak;
 
    for (int i = 0; i <= tree.maxDepth; i++) {
        sum = banyak = 0;
        scanGivenLevel(tree.root, i, &sum, &banyak);
        printf("Level %d = %.2f\n", i, sum/banyak);
    }
} 
 
BSTNode *_insert(BSTNode *root, float value) 
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
 
void insert(BSTree *tree, float value) 
{
    tree->root = _insert(tree->root, value);
    if (currNodeDepth > tree->maxDepth) {
        tree->maxDepth = currNodeDepth;
    }
}
 
BSTNode *createNode(float value) 
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