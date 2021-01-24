#include <stdio.h>
#include <stdbool.h>

#include "BST.h"

int main(void)
{
    BSTree tree;
    init(&tree);

    insert(&tree, 6);
    insert(&tree, 1);
    insert(&tree, 8);
    insert(&tree, 12);
    insert(&tree, 1);
    insert(&tree, 3);
    insert(&tree, 7);

    preorder(tree.root);
    puts("");
    inorder(tree.root);
    puts("");
    postorder(tree.root);
    puts("");

    delete(&tree, 8);
    delete(&tree, 6);

    inorder(tree.root);
    puts("");

    if (find(tree.root, 1)) printf("Founded\n");
    else printf("Not found\n");

    if (find(tree.root, 10)) printf("Founded\n");
    else printf("Not found\n");

    BSTNode *temp = search(tree.root, 3);
    if (temp) printf("Search Founded\n");
    else printf("Search Not Founded\n");

    temp = findMinNode(tree.root);
    printf("Min node: %d\n", temp->key);

    freeALL(&tree.root);
    tree.root = NULL;

    return 0;
}