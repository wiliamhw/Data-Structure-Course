// Ninja saga

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue
{
    int hp, atk, spd, r_spd;
    struct queue *front;
    struct queue *rear;
} queue;

typedef struct Data
{
    queue *player;
    queue *tail;
} Data;

Data data[2];

// int ronde;
int p_data[2];

// 0 = player
// 1 = enemy

void unload(int i);
void push(int cek, int hp, int atk, int spd, int r_spd);
void printElement(int n);
void printALL(void);

void fight(void);
bool End(void);
void attack(queue *trav, int n);
void popTail(int n);

int main(void)
{
    for (int i = 0; i < 2; i++)
    {
        data[i].player = NULL;
    }

    // Get Input
    int hp, atk, spd;
    scanf("%d %d", &p_data[0], &p_data[1]);

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < p_data[j]; i++)
        {
            scanf("%d %d %d", &hp, &atk, &spd);
            push(j, hp, atk, spd, spd);
        }
    }

    // Print database
    // printALL();

    fight();
    for (int i = 0; i < 2; i++) unload(i);
    return 0;
}

void fight(void)
{
    // ronde = 1;

    while (1)
    {
        // printf("---------------------RONDE %d:--------------------\n", ronde);
        // printALL();

        for (int i = 0; i < 2; i++)
        {
            queue *trav = data[i].player;

            while (trav)
            {
                if (trav->spd >= 100)
                {
                    // printf("---P%d attack---\n\n", i+1);
                    if (End()) return;;
                    attack(trav, i);
                }
                trav->spd += trav->r_spd;
                trav = trav->rear;
            }
        }
        // ronde++;
    }
    return;
}

void attack(queue *trav, int n)
{
    if (!trav) return;

    int lawan;
    if (n == 1) lawan = 0;
    else lawan = 1;

    data[lawan].tail->hp -= trav->atk;
    trav->spd -= 100;

    if (data[lawan].tail->hp <= 0)
    {
        popTail(lawan);
    }

    return;
}

void popTail(int n)
{
    if (!data[n].player) return;

    queue *trav = data[n].tail;

    if (trav->front)
    {
        trav->front->rear = NULL;
        data[n].tail = trav->front;
        free(trav);
    }
    else // Last one standing
    {
        free(trav);
        data[n].tail = NULL;
        data[n].player = NULL;
    }
    return;
}

bool End(void)
{
    if (!data[1].player)
    {
        printf("You Won!\n");
        return true;
    }
    else if (!data[0].player)
    {
        printf("Game Over.\n");
        return true;
    }
    else return false;
}

void push(int cek, int hp, int atk, int spd, int r_spd)
{
    queue *n = malloc(sizeof(queue));
    if (!n) return;
    n->hp = hp;
    n->atk = atk;
    n->spd = spd;
    n->r_spd = r_spd;

    // Make new
    if (!data[cek].player)
    {
        n->rear = NULL;
        n->front = NULL;
        data[cek].player = n;
        data[cek].tail = n;
    }
    else
    {
        queue *trav = data[cek].player;

        // Push top (front)
        if (n->spd > trav->spd)
        {
            n->front = NULL;
            n->rear = trav;
            trav->front = n;
            data[cek].player = n;
        }
        else // Push bot (rear) or mid
        {
            while (trav->rear && n->spd < trav->rear->spd)
            {
                trav = trav->rear;
            }

            n->front = trav;
            n->rear = trav->rear;
            if (!n->rear) data[cek].tail = n;
            else trav->rear->front = n;
            trav->rear = n;
        }
    }
    return;
}

void unload(int i)
{
    queue *trav = data[i].player;

    while (trav)
    {
        queue *tmp = trav;
        trav = trav->rear;
        free(tmp);
    }
    return;
}

void printElement(int n)
{
    queue *trav = data[n].player;

    while (trav)
    {
        printf("Hp: %d Atk: %d Spd: %d r_spd: %d\n",
            trav->hp, trav->atk, trav->spd, trav->r_spd);
        trav = trav->rear;

    }
    return;
}

void printALL(void)
{
    // Print database
    for (int i = 0; i < 2; i++)
    {
        printf("--- Player %d\n", i + 1);
        printElement(i);

        // Print tail
        printf("--- TAIL: Hp: %d Atk: %d", data[i].tail->hp, data[i].tail->atk);
        printf(" Spd: %d r_spd: %d ---\n\n", data[i].tail->spd, data[i].tail->r_spd);
    }
}