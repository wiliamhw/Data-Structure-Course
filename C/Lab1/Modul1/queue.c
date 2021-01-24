
/* Modul 1, No.3
* Single Linked List
* Queue
* MEYNIMPAN STRING (maks 100 char)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGHT 100
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef struct queue
{
    char word[LENGHT + 1];
    struct queue *next;
} queue;

void unload(queue *head); // Unload all from memory
void dequeue(queue **head); // Unload tail from memory
void randomAdd(queue **head); // RNG
void enqueue(queue **head, char in[LENGHT + 1]); // Masukin string di head
void printElement(queue *head); // Print All
char *getFront(queue *head); // Get front (head)

int main(void)
{
    queue *head = NULL;

    // Isi Linked List
    char in[LENGHT + 1];
    printf("Input: ");
    while (1)
    {
        scanf("%s", in);
        if (strcmp(in, "stop") == 0) break;
        else if (strcmp(in, "random") == 0) randomAdd(&head);
        else enqueue(&head, in);
    }
    printf("\n");
    printElement(head);

    dequeue(&head);
    printElement(head);

    printf("%s\n", getFront(head));
    if (head) unload(head);
    return 0;
}

char *getFront(queue *head)
{
    return head->word;
}

void unload(queue *head)
{
    queue *trav = head;

    // Traverse every linked list
    while (trav)
    {
        queue *tmp = trav;
        trav = trav->next;
        free(tmp);
    }
}

void dequeue(queue **head)
{
    queue *tmp = *head;
    *head = tmp->next;
    free(tmp);
    return;
}

void printElement(queue *head)
{
    queue *trav = head;
    while (trav)
    {
        printf("%s ", trav->word);
        trav = trav->next;
    }
    printf("\n");
    return;
}

void enqueue(queue **top, char in[LENGHT + 1])
{
    queue *trav = *top;

    // Traverse to back
    if (trav)
    {
    	while (trav->next)
        	trav = trav->next;
	}

    // Make new queue
    queue *n = malloc(sizeof(queue));
    if (!n) return;
    strcpy(n->word, in);
    n->next = NULL;

    // Insert queue
    if (trav)
    	trav->next = n;
    else *top = n;
    return;
}

void randomAdd(queue **head)
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
        enqueue(head, randString);
    }
    printf("\n");
    return;
}