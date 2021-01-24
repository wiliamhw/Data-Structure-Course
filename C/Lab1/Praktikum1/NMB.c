/* front
*  rear
*  rear <--> front
* Josephus
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int x;
    struct queue *front;
    struct queue *rear;
} queue;

typedef struct node
{
    queue *tail;
    queue *head;
    int size;
} node;

node data;

void init(void);
void unload(void);
void printElement(void);
void enqueue(int num);
void makecircular(void);

void josephus(int n, int k);

int main(void)
{
    init();

    // Get input
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++)
    {
        enqueue(i);
    }
    makecircular();

    josephus(n, k);
    unload();
    return 0;
}

void josephus(int n, int k)
{
    queue *trav = NULL;
    int move, size;
    size = data.size;

    if (k >= 0) // Geser kanan
    {
        while (data.head->rear)
        {
            trav = data.head;
            // printElement();

            if (k >= size) move = k % size;
            else move = k;

            for (int i = 0; i < move; i++)
                trav = trav->rear;

            // Hapus trav + pindahin head ke rear
            if (size > 2)
            {
                trav->rear->front = trav->front;
                trav->front->rear = trav->rear;
            }
            else // Kalo cuman dua elemen
            {
                trav->rear->front = NULL;
                trav->front->rear = NULL;
            }

            data.head = trav->rear;
            printf("%d ", trav->x);
            free(trav);
            size--;
            // printf("\nSize: %d\n\n", size);
        }
    }
    else // Geser kiri
    {
        k = abs(k);
        while (data.head->front)
        {
            trav = data.head;
            // printElement();

            if (k >= size) move = k % size;
            else move = k;

            for (int i = 0; i < move; i++)
                trav = trav->front;

            // Hapus trav + pindahin head ke front
            if (size > 2)
            {
                trav->front->rear = trav->rear;
                trav->rear->front = trav->front;
            }
            else // Kalo cuman dua elemen
            {
                trav->rear->front = NULL;
                trav->front->rear = NULL;
            }

            data.head = trav->front;
            printf("%d ", trav->x);
            free(trav);
            size--;
            // printf("\nSize: %d\n", size);
        }
    }
    printf("~ %d\n", data.head->x);
    return;
}

void makecircular(void)
{
    data.head->front = data.tail;
    data.tail->rear = data.head;
    data.tail = NULL;
    return;
}

void enqueue(int num)
{
    queue *n = malloc(sizeof(queue));
    if (!n) return;
    n->x = num;
    n->rear = NULL;

    // Make new
    if (!data.head)
    {
        n->front = NULL;
        data.head = n; 
    }
    else // Push bot (rear)
    {
        n->front = data.tail;
        n->front->rear = n;
    }
    data.tail = n;
    data.size++;
    return;
}

void printElement(void)
{
    queue *trav = data.head;

    printf("Num: ");

    for (int i = 0; i < data.size && trav; i++)
    {
        printf("%d ", trav->x);
        trav = trav->rear;
    }
    printf("\n");
    return;
}

void unload(void)
{
    queue *trav = data.head;

    for (int i = 0; i < data.size && trav; i++)
    {
        queue *tmp = trav;
        trav = trav->rear;
        free(tmp);
    }
    return;
}

void init(void)
{
    data.tail = NULL;
    data.head = NULL;
    data.size = 0;
    return;
}