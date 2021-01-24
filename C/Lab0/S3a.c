/* Modul 0, No.3
* Linked List
*   - fungsi untuk setiap element int Linked List
*   - menyimpan string
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGHT 100
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef struct node
{
    char word[LENGHT + 1];
    struct node *next;
} node;

void unload(node *head); // Unload dictionary from memory
void randomAdd(node **head); // RNG
void pushFront(node **head, char in[LENGHT + 1]); // Masukin angka di head
void forEachElement(node *head, char *command); // Perintah untuk tiap elemen
    /* command: random = randomize input
                stop = stop input
    */

int main(void)
{
    node *head = NULL;

    // Isi Linked List
    char in[LENGHT + 1];
    printf("Input: ");
    while (1)
    {
        scanf("%s", in);
        if (strcmp(in, "stop") == 0) break;
        else if (strcmp(in, "random") == 0) randomAdd(&head);
        else pushFront(&head, in);
    }

    printf("\n");
    forEachElement(head, "printElement");
    unload(head);
    return 0;
}

void forEachElement(node *head, char *command)
{
    node *trav = head;

    if (strcmp((char*)"printElement", command) == 0)
    {
        while (trav)
        {
            printf("%s ", trav->word);
            trav = trav->next;
        }
    }
    else printf("Fail Command");

    printf("\n");
    return;
}

void randomAdd(node **head)
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

        pushFront(head, randString);
    }
    printf("\n");
    return;
}

void pushFront(node **head, char in[LENGHT + 1])
{
    // Make new node
    node *n = malloc(sizeof(node));
    strcpy(n->word, in);

    // Insert node (push front)
    if (head) n->next = *head;
    else n->next = NULL;

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