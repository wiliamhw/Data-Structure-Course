/* Modul 1
* Linked list
* Stack untuk cek palindrom
* SIMPAN CHAR
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    char c;
    struct node *next;
} node;

void push(node **head, char huruf);
char top(node *head);
void pop(node **head);
void unload(node *head);
// void forEachElement(node *head, char *command); // Perintah untuk tiap elemen
    /* command: random = randomize input
                stop = stop input
    */

int main(void)
{
    node *head = NULL;

    int counter, len, i_half, i;
    len = counter = 0;

    char word[101];
    for (i = 0; i < 100; i++)
    {
        scanf("%c", &word[i]);
        if (word[i] == '\n') break;
        len++;
    }
    word[++i] = '\0';

    i_half = len / 2;

    for (i = 0; i < i_half; i++)
    {
        push(&head, word[i]);
    }
    if (len % 2 != 0) i++; // If len = ganjil

    // forEachElement(head, "printElement");

    for (; i < len; i++)
    {
        if (word[i] == top(head))
            counter++;
        pop(&head);
    }

    if (counter == i_half) printf("Palindrom :)\n");
    else printf("Bukan palindrom T^T\n");

    if (head) unload(head);
    return 0 ;
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

void pop(node **head)
{
    if (*head)
    {
        node *trav = *head;
        *head = trav->next;
        free(trav);
    }
    return;
}

char top(node *head)
{
    if (!head) return '\0';
    node *trav = head;
    return trav->c;
}

void push(node **head, char huruf)
{
    // Make new node
    node *n = malloc(sizeof(node));
    if (!n) return;
    n->c = huruf;

    // Insert node (push front)
    if (head) n->next = *head;
    else n->next = NULL;

    // Change head
    *head = n;
    return;
}

// void forEachElement(node *head, char *command)
// {
//     node *trav = head;

//     if (strcmp((char*)"printElement", command) == 0)
//     {
//         while (trav)
//         {
//             printf("%c ", trav->c);
//             trav = trav->next;
//         }
//     }
//     else printf("Fail Command");

//     printf("\n");
//     return;
// }