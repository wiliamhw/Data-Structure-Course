#include <stdio.h>
#include <stdbool.h>

#include "AVL.h"

int main(void)
{
    AVLTree tree;
    init(&tree);

    insert(&tree, 6);
    insert(&tree, 1);
    insert(&tree, 0);
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

    delete(&tree, 6);
    inorder(tree.root);
    puts("");

    delete(&tree, 12);
    inorder(tree.root);
    puts("");

    delete(&tree, 0);
    inorder(tree.root);
    puts("");

    if (find(tree.root, 1)) printf("Founded\n");
    else printf("Not found\n");

    if (find(tree.root, 10)) printf("Founded\n");
    else printf("Not found\n");

    int tmp = findMin(tree.root);
    printf("Min node: %d\n", tmp);

    tmp = findMax(tree.root);
    printf("Max node: %d\n", tmp);

    freeALL(&tree.root);

    return 0;
}
