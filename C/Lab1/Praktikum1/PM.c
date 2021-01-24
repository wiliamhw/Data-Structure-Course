// Prev <--> Next
// Palindrom

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int x;
    struct node *next;
} node;

node *stack[2];
// stack[0] = main data
// stack[1] = buffer

void init(void);
void push(int n, int num);
void pop(int n);
void unload(int n);

int balance(int N);

int main(void)
{
    init();

    int N, in;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &in);
        push(0, in);
    }

    int count = balance(N);
    printf("%d\n", count);
    unload(0);
    return 0;
}

int balance(int N)
{
    int max, count, size;
    max = count = size = 0;

    node *trav = stack[0];

    // min = buka kurung, plus = tutup kurung
    // krn pakai stack jdi kebalik
    for (int i = 0; i < N && trav; i++)
    {
        if (trav->x < 0) 
        {
            push(1, abs(trav->x));
            size++;
        }

        else if (trav->x > 0 && stack[1])
        {
            if (trav->x == stack[1]->x)
            {
                pop(1);
                count += 2;
            }
            else // Pop-all stack
            {
                count = 0;
                for (int j = 0; j < size; j++)
                {
                    pop(1);
                }
            }      
        }
        if (count > max) max = count;
        trav = trav->next;
    }

    unload(1);
    return max;
}

void pop(int n)
{
    if (stack[n])
    {
        node *trav = stack[n];
        stack[n] = trav->next;
        free(trav);
    }
    return;
}

void push(int n, int num) // Pushfront
{
    // Make new node
    node *new = malloc(sizeof(node));
    if (!new) return;
    new->x = num;

    // Make new
    if (!stack[n]) new->next = NULL;
    else new->next = stack[n];

    stack[n] = new;
    return;
}

void unload(int n)
{
    node *trav = stack[n];

    // Traverse every linked list
    while (trav)
    {
        node *tmp = trav;
        trav = trav->next;
        free(tmp);
    }
}

void init(void)
{
    stack[0] = NULL;
    stack[1] = NULL;
}