// https://www.spoj.com/problems/ADDREV/

#include <stdio.h>

int reverse(int value);

int main(void) {
    int loop, n1, n2;
    scanf("%d", &loop);

    for (int i = 0; i < loop; i++) {
        scanf("%d %d", &n1, &n2);
        n1 = reverse(n1);
        n2 = reverse(n2);
        printf("%d\n", reverse(n1 + n2));
    }
    return 0;
}

int reverse(int value) {
    int temp = 0;
    while (value > 0) {
        temp *= 10;
        temp += value % 10;;
        value /= 10;
    }
    return temp;
}