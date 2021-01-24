/* Modul 1, No.3
* Singly Linked List
* Stack
* MEYNIMPAN STRING (maks 100 char)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGHT 100
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

typedef struct node
{
    char word[LENGHT + 1];
    struct node *next;
} node;

void unload(node *top); // Unload all from memory
void pop(node **top); // Unload top from memory
void randomAdd(node **top); // RNG
void push(node **top, char in[LENGHT + 1]); // Masukin angka di top
void printElement(node *top); // Print All
char *getTop(node *top); // Get top

int main(void)
{
    node *top = NULL;

    // Isi Linked List
    char in[LENGHT + 1];
    printf("Input: ");
    while (1)
    {
        scanf("%s", in);
        if (strcmp(in, "stop") == 0) break;
        else if (strcmp(in, "random") == 0) randomAdd(&top);
        else push(&top, in);
    }
    printf("\n");
    printElement(top);

    pop(&top);
    printElement(top);

    printf("%s\n", getTop(top));
    if (top) unload(top);
    return 0;
}

char *getTop(node *top)
{
    return top->word;
}

void unload(node *top)
{
    node *trav = top;

    // Traverse every linked list
    while (trav)
    {
        node *tmp = trav;
        trav = trav->next;
        free(tmp);
    }
}

void pop(node **top)
{
    node *tmp = *top;
    *top = tmp->next;
    free(tmp);
}

void printElement(node *top)
{
    node *trav = top;
    while (trav)
    {
        printf("%s ", trav->word);
        trav = trav->next;
    }
    printf("\n");
    return;
}

void push(node **top, char in[LENGHT + 1])
{
    // Make new node
    node *n = malloc(sizeof(node));
    strcpy(n->word, in);

    // Insert node (push top)
    if (top) n->next = *top;
    else n->next = NULL;

    *top = n;
    return;
}

void randomAdd(node **top)
{
    srand(time(NULL));

    int kata = rand() % 8 + 3; // Maks 10 kata, min 3 kata

    printf("Random Word: ");
    for (int i = 0; i < kata; i++)
    {
        int len = rand() % 8 + 3; // Maks 10 huruf, min 3 huruf per kata
        char randString[len + 1];

        for (int j = 0; j < len; j++)
        {
            int key = rand() % (int) (sizeof(charset) - 1);
            randString[j] = charset[key];
        }
        randString[len] = '\0';

        printf("%s ", randString);
        push(top, randString);
    }
    printf("\n");
    return;
}