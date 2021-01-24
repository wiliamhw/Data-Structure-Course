// https://www.hackerrank.com/challenges/array-left-rotation/problem

#include <stdio.h>

int main(void)
{
    int banyak, geser;
    scanf("%d %d", &banyak, &geser);

    int num[banyak], tmp[banyak];
    for (int i = 0; i < banyak; i++)
    {
        scanf("%d", &num[i]);
        tmp[i] = num[i];
    }

    int pertama = geser % banyak;
    for (int i = 0; i < banyak; i++)
    {
        num[i] = tmp[pertama++];
        if (pertama >= banyak) pertama = 0;
    }

    for (int i = 0; i < banyak; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\n");
    return 0;
}