// https://vjudge.net/contest/367564#problem/D

#include <stdio.h>

int main(void) {
    long long int Case, Time, length;
    long long int sum = 0;
    scanf("%lld", &Case);

    while (Case-- > 0) {
        scanf("%lld %lld", &Time, &length);

        while (sum < Time) sum++;

        sum += length;
    }
    printf("%lld\n", sum);
    return 0;
}