#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    FILE *log = fopen("case.txt", "w");
    int loop = 10;
    int limit = 100000;
    int bawah = 10000;

    fprintf(log, "%d\n", loop);

    clock_t tStart = clock();
    srand(time(NULL));

    for (int i = 0; i < loop; i++) {
        int number = bawah + (rand() % (limit - bawah + 1));
        fprintf(log, "%d\n", number);
    }

    fclose(log);
    return 0;
}