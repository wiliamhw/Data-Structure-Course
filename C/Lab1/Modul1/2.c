/* Modul 1, No.2
* Double Linked list
* Priority Queue (bil.tertinggi = prioritas)
* MEYNIMPAN INT
* HEAD -> top = NULL, bot = rantai
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct queue
{
    int id, prioritas;
    struct queue *top;
    struct queue *bot;
} queue;

unsigned int size = 0;

void push(queue **head, int id, int prioritas);
void pop(queue **head);
int top(queue *head);
void unload(queue *head);
void printElement(queue *head); // Print element (node)


int main(void)
{
    queue *head = NULL;

    char perintah[7];
    int org, id, prioritas;
    scanf("%d", &org);

    for (int i = 0; i < org; i++)
    {
        scanf("%s", perintah);
        if (strcmp(perintah, "MASUK") == 0)
        {
            scanf("%d %d", &id, &prioritas);
            push(&head, id, prioritas);
        }
        else
        {
            printElement(head);
            printf("%d\n", top(head));
            pop(&head);
        }
        getchar();
    }
    if (head) unload(head);
    return 0;
}

void printElement(queue *head)
{
    queue *trav = head;
    while (trav)
    {
        printf("%d %d\n", trav->id, trav->prioritas);
        trav = trav->bot;
    }
    printf("\n");
    return;
}

void unload(queue *head)
{
    queue *trav = head;

    // Traverse every linked list
    while (trav)
    {
        queue *tmp = trav;
        trav = trav->bot;
        free(tmp);
    }
}

int top(queue *head)
{
    if (!head) return 0;
    queue *trav = head;
    return trav->id;
}

void pop(queue **head)
{
    if (*head)
    {
        queue *trav = *head;
        *head = trav->bot;
        free(trav);
    }
    return;
}

void push(queue **head, int id, int prioritas)
{
    queue *n = malloc(sizeof(queue));
    if (!n) return;
    n->id = id;
    n->prioritas = prioritas;

    if (!*head)
    {
        n->bot = NULL;
        n->top = NULL;
        *head = n;
    }
    else
    {
        queue *trav = *head;
        if (n->prioritas > trav->prioritas)
        {
            n->top = NULL;
            n->bot = trav;
            trav->top = n;
            *head = n;
        }
        else
        {
            while (trav->bot && n->prioritas < trav->bot->prioritas)
            {
                trav = trav->bot;
            }

            n->top = trav;
            n->bot = trav->bot;
            trav->bot = n;
            if (n->top)
                n->top->bot = n;
        }
    }
    return;
}