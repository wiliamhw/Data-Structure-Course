#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    FILE *log = fopen("case.txt", "w");
    int N = 20000;
    int t = 100000;
    int c = 2000;
    int ab = N-2;
    int bawah = 0;

    clock_t tStart = clock();
    srand(time(NULL));

    int N_r = N;
    fprintf(log, "%d\n", N_r);

    // int t_r = bawah + (rand() % (t - bawah + 1));
    int t_r = t;
    fprintf(log, "%d\n", t_r);

    for (int i = 0; i < t_r; i++) {
        // int c_r = bawah + (rand() % (c - bawah + 1));
        int c_r = c;
        fprintf(log, "%d\n", c_r);

        for (int j = 0; j < c_r; j++) {
            int a_r = bawah + (rand() % (ab - bawah + 1));
            int b_r = bawah + (rand() % (ab - bawah + 1));
            fprintf(log, "%d %d\n", a_r, b_r);
        }
    }

    fclose(log);
    return 0;
}