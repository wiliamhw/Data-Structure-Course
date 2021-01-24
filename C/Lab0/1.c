/* Modul 0, No.1
* Linked List -> fungsi untuk setiap element int Linked List
* MENYIMPAN INT
* Double pointer = pointer to pointer
*   utk ganti head --> hrs di pass dari main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct node
{
    int x;
    struct node *next;
} node;

unsigned int size = 0;

void pushFront(node **head, int num); // Masukin angka di head
void pushBack(node *head, int num); // Masukin angka di tail
void insertAt(node **head, int index, int num); // Masukin angka di index tertentu
int back(node *head); // Ambil angka paling belakang
int front(node *head); // Ambil angka terdepan
int getAt(node *head, int index); // Ambil angka pada index tertentu
void popBack(node *head); // Buang belakang
void popFront(node **head); // Buang depan
void removeAt(node **head, int index); // Remove data di index ke sekian

void unload(node *head); // Unload dictionary from memory
void randomAdd(node **head); // RNG
void forEachElement(node *head, char *command); // Perintah untuk tiap elemen
    // Command
    void printElement(node *head); // Print element (node)
    void multiply2(node *head); // Mengalikan setiap element dgn 2
    void reverseEach(node *head); // Membalik setiap digit
    void sumDigit(node *head); // Ganti elemen dengan jumlah digitnya

int main(void)
{
    node *head = NULL;

    // Isi Linked List
    int in;
    printf("Input: ");
    while (1)
    {
        if (!scanf("%d", &in)) break;
        else if (in == 0) randomAdd(&head);
        else pushFront(&head, in);
    }

    pushBack(head, 505);
    insertAt(&head, 1, 10000);
    insertAt(&head, 100000, 321);

    forEachElement(head, "printElement");

    forEachElement(head, "multiply2");
    forEachElement(head, "printElement");

    forEachElement(head, "reverseEach");
    forEachElement(head, "printElement");

    forEachElement(head, "sumDigit");
    forEachElement(head, "printElement");

    popBack(head);
    popFront(&head);
    forEachElement(head, "printElement");

    printf("Front: %d\n", front(head));
    printf("Back: %d\n", back(head));
    printf("Get at 3: %d\n", getAt(head, 3));

    unload(head);
    return 0;
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

void popBack(node *head)
{
    if (head)
    {
        node *trav = head;

        // Traverse every linked list
        while (trav->next->next)
            trav = trav->next;

        free(trav->next);
        trav->next = NULL;
    }
    return;
}

int getAt(node *head, int index)
{
    if (!head) return 0;

    if (index == 0) return front(head);
    else if (index >= size - 1) return back(head);

    node *trav = head;

    // Traverse every linked list
    for (int i = 0; i < index && trav->next; i++)
    {
        trav = trav->next;
    }

    return trav->x;
}

int front(node *head)
{
    if (!head) return 0;
    node *trav = head;
    return trav->x;
}

int back(node *head)
{
    if (!head) return 0;
    node *trav = head;

    // Traverse every linked list
    while (trav->next)
        trav = trav->next;

    return trav->x;
}

void insertAt(node **head, int index, int num)
{
    if (index == 0 || !*head) pushFront(head, num);
    else if (index >= size - 1) pushBack(*head, num);
    else
    {
        node *trav = *head;
        for (int i = 0; i < index - 1; i++)
        {
            if (trav->next)
                trav = trav->next;
            else
            {
                pushBack(*head, num);
                return;
            }
        }
        // Make new node
        node *n = malloc(sizeof(node));
        if (!n) return;
        n->x = num;

        // Insert node
        n->next = trav->next;
        trav->next = n;
        size++;
    }
    return;
}

void pushBack(node *head, int num)
{
    if (!head) return;

    node *trav = head;

    // Traverse to back
    while (trav->next)
        trav = trav->next;

    // Make new node
    node *n = malloc(sizeof(node));
    if (!n) return;
    n->x = num;
    n->next = NULL;

    // Insert node
    trav->next = n;
    size++;
}

void removeAt(node **head, int index)
{
    if (!*head) return;

    node *trav = *head;

    if (index >= size) index = size - 1; // Popback
    else if (index < 0) index = 0; // Popfront

    for (int i = 0; i < index - 1; i++)
        trav = trav->next;

    node *nextHead = trav->next->next;
    free(trav->next);
    trav->next = nextHead;
    size--;

    return;
}

void printElement(node *head)
{
    node *trav = head;
    while (trav)
    {
        printf("%d ", trav->x);
        trav = trav->next;
    }
    printf("\n");
    return;
}

void multiply2(node *head)
{
    node *trav = head;
    while (trav)
    {
        trav->x *= 2;
        trav = trav->next;
    }
    return;
}

void reverseEach(node *head)
{
    node *trav = head;
    while (trav)
    {
        int num = trav->x;
        trav->x= 0;
        for (int i = 0; num != 0; i++)
        {
            trav->x *= 10;
            int adder = num % 10; // Ambil dari belakang
            trav->x += adder;
            num /= 10;
        }
        trav = trav->next;
    }
    return;
}

void sumDigit(node *head)
{
    node *trav = head;
    while (trav)
    {
        int num = trav->x;
        trav->x = 0;
        while (num != 0)
        {
            trav->x += (num % 10);
            num /= 10;
        }
        trav = trav->next;
    }
    return;
}

void forEachElement(node *head, char *command)
{
    if (strcmp((char*)"printElement", command) == 0)
        printElement(head);

    else if (strcmp((char*)"multiply2", command) == 0)
        multiply2(head);

    else if (strcmp((char*)"reverseEach", command) == 0)
        reverseEach(head);

    else if (strcmp((char*)"sumDigit", command) == 0)
        sumDigit(head);

    else printf("Fail Command\n");

    return;
}

void randomAdd(node **head)
{
    srand(time(NULL));

    // Maks 10 item, min 3 item
    int loop = rand() % 8 + 3;

    printf("Random Input: ");
    for (int i = 0; i < loop; i++)
    {
        // Angka maks = 100
        int num = rand() % 100;
        printf("%d ", num);

        pushFront(head, num);
    }
    printf("\n");
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
    size++;
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