#include <stdio.h>

int main(void) {
    int n, k;
    scanf("%d %d", n, k);

    char gate[n];
    for (int i = 0; i < n; i++) {
        scanf("%c", &gate[i]);
    }

    int count[26], index;
    for (int i = 0; i < n - 1; i++) {
        index = (int) gate[i] - 65;
        next = (int) gate[i + 1] - 65;

        count[index]++;

        if (gate[i + 1])
    }
}