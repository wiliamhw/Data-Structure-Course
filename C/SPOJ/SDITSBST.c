/* BST tanpa elemen yg sama 
https://www.spoj.com/problems/SDITSBST/
*/
 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
typedef struct bstnode_t {
    unsigned long long key;
    unsigned long long rightsize;
    struct bstnode_t *left, *right;
} BSTNode;
 
typedef struct BSTree {
    BSTNode *root;
    unsigned long long size;
} BSTree;
 
void init(BSTree *tree);
BSTNode *createNode(unsigned long long value); // Buat node baru
BSTNode *insert(BSTNode *root, unsigned long long value); // Masukin node
BSTNode *search(BSTNode *root, unsigned long long value, unsigned long long *counter);
 
int main(void)
{
    BSTree tree;
    init(&tree);

    unsigned long long loop, opcode;
    unsigned long long value, counter;
    scanf("%d", &loop);
 
    for (unsigned long long i = 0; i < loop; i++)
    {
        counter = 0;
        scanf("%llu", &opcode);
 
        if (opcode != 1 && opcode != 2) {
            printf("Invalid opcode\n");
            return 1;
        }
        
        scanf("%llu", &value);
 
        if (opcode == 1) {
            tree.root = insert(tree.root, value);
            tree.size++;
        }
        
        else {
            if (search(tree.root, value, &counter))
                printf("%llu\n", counter);
            else
                printf("Data tidak ada\n");
        }
    }
    
    return 0;
}
 
BSTNode *createNode(unsigned long long value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->rightsize = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *search(BSTNode *root, unsigned long long value, unsigned long long *counter) {
    while (root)
    {
        if (value > root->key) {
            root = root->right;
        }
 
        else if (value < root->key) {
            *counter += root->rightsize + 1;
            root = root->left;
        }
        else {
            *counter += root->rightsize + 1;
            return root;
        }
    }
    return root;
}
 
BSTNode *insert(BSTNode *root, unsigned long long value)
{
    if (!root) {
        BSTNode *temp = createNode(value);
        return temp;
    }
 
    else if (value < root->key) {
        root->left = insert(root->left, value);
    }
 
    else if (value > root->key) {
        root->rightsize++;
        root->right = insert(root->right, value);
    }
 
    return root;
}

void init(BSTree *tree) {
    tree->root = NULL;
    tree->size = 0;
}
 