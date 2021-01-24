// Cek urutan stack dari top

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    int x;
    struct node *next;
} node;

void pushFront(node **head, int num); // Masukin angka di head
int front(node *head); // Ambil angka terdepan
void popFront(node **head); // Buang depan
void search(node *head, int item, int loop, int size);

void unload(node *head); // Unload 

int main(void)
{
    node *head = NULL;

    // Isi Linked List
    int loop, in, item;
    scanf("%d", &loop);

    for (int i = 0; i < loop; i++)
    {
        scanf("%d", &in);
        pushFront(&head, in);
    }

    scanf("%d", &item);

    // Search item
    search(head, item, loop, loop);

    unload(head);
    return 0;
}

void search(node *head, int item, int loop, int size)
{
    node *trav = head;
    int counter = 0;

    // Traverse every linked list
    for (int i = 1; i < size; i++)
    {
        trav = trav->next;
        counter++;
        if (item == trav->x)
        {
            printf("%d\n", counter);
            return;
        }
    }
    printf("Barangnya gak ada beb\n");
    return;
}

void popFront(node **head)
{
    if (*head)
    {
        node *trav = *head;
        *head = trav->next;
        free(trav);
    }
    return;
}

int front(node *head)
{
    if (!head) return 0;
    node *trav = head;
    return trav->x;
}

void pushFront(node **head, int num)
{
    // Make new node
    node *n = malloc(sizeof(node));
    if (!n) return;
    n->x = num;

    // Insert node (push front)
    if (head) n->next = *head;
    else n->next = NULL;

    // Change head
    *head = n;
    return;
}

void unload(node *head)
{
    node *trav = head;

    // Traverse every linked list
    while (trav)
    {
        node *tmp = trav;
        trav = trav->next;
        free(tmp);
    }
}