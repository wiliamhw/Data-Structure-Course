// https://www.spoj.com/problems/FCTRL/

#include <stdio.h>
#include <math.h>

int countZero(int input);

int main(void)
{
    int loop, input;
    scanf("%d", &loop);

    while (loop-- != 0)
    {
        scanf("%d", &input);

        printf("%d\n", countZero(input));
    }
    return 0;
}

int countZero(int input) {
    int counter, tmp, result;
    counter = 0;

    for (int i = 1; ; i++) {
        result = 0;
        tmp = input;
        result += input / pow(5, i);

        if (result == 0) break;
        else counter += result;
    }
    return counter;
}