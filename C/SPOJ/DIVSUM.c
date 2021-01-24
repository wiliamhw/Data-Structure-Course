// https://www.spoj.com/problems/DIVSUM/

#include <stdio.h>
#include <math.h>

int main(void) {
    int loop, input;
    scanf("%d", &loop);

    while (loop-- > 0) {
        scanf("%d", &input);
        int sum = 1;

        if (input == 1) sum--;
        else {
            int root = sqrt(input);

            for (int i = 2; i <= root; i++) {
                if (input % i == 0) {
                    if (i == input / i)
                        sum += i;
                    else
                        sum += i + (input / i);
                }
            }
        }
        
        printf("%d\n", sum);
    }
    return 0;
}