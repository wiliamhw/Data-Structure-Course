// https://vjudge.net/contest/367564#problem/C

#include <stdio.h>

int main(void) {
    long long int n;
    scanf("%lld", &n);

    long long int kontes[n];
    for (long long int i = 0; i < n; i++) {
        scanf("%lld", &kontes[i]);
    }

    long long int day = 0;
    long long int sisa = 0;
    long long int j = 1;

    for (long long int i = n - 1; i >= 0; i--) {
        sisa += kontes[i];
        sisa -= j;

        if (sisa >= 0) {
            day++;
            j++;
        }
        else break;
    }

    printf("%lld\n", day);
    return 0;
}