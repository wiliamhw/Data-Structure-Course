// https://www.hackerrank.com/challenges/sparse-arrays/problem

#include <stdio.h>
#include <string.h>

int main(void)
{
    int b_string; // Banyak string
    scanf("%d", &b_string);
    char string[b_string][b_string];

    for (int i = 0; i < b_string; i++)
    {
        scanf("%s", string[i]);
    }

    int b_query; // Banyak query;
    scanf("%d", &b_query);
    char query[b_query];
    int counter[b_query];

    for (int i = 0; i < b_query; i++)
    {
        counter[i] = 0;
        scanf("%s", query);

        for (int j = 0; j < b_string; j++)
        {
            if (strcmp(query, string[j]) == 0)
                counter[i]++;
        }
    }

    for (int i = 0; i < b_query; i++)
        printf("%d\n", counter[i]);

    return 0;
}