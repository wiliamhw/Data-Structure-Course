#include <stdio.h>
// #include <sys/resource.h>

#include "utility.h"
#include "sorter.h"
#include "cs50.h"

int main(void)
{
    // struct rusage before, after;
    int n, max;
    n = max = 10;
    // int n = get_int("Masukan banyak angka => ");
    // int max = get_int("Angka maksimal => ");
    char a[n];

    // getrusage(RUSAGE_SELF, &before);
    SrandArr(a, n);
    // getrusage(RUSAGE_SELF, &after);

    // double _time = calculate(&before, &after);

    printf("%s\n", a);
    // printf("Waktu = %lf\n", _time);

    return 0;
}