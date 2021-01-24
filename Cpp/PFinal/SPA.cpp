#include <iostream>
using namespace std;

int Un(int, int);
long long int Sn(int, int);
long long int getDigit(long long int sum);

int main() {
    while (1) {
        int n;
        cin >> n;

        int b = (n - 3)/2;
        long long int sum;

        if (n <= 2) {
            cout << n << endl;
            return 0;
        }
        else if (n % 2 == 0) {
            sum = (Sn(n, b) * 2) + 2;
        } 
        else {
            sum = (Sn(n+1, b) * 2) + 2 - Un(n, b);
        }
        long long int y = getDigit(sum);
        sum += y;

        while (1) {
            long long int z = getDigit(sum);

            if (z == y) break;
            else {
                long long int diff = abs(z - y);
                sum += diff;
                y = z;
            }
        }
        cout << sum << endl;
    }

    return 0;
}

long long int getDigit(long long int sum) {
    return (sum / 10);
}

long long int Sn(int n, int b) {
    long long int x = (n - 1)/2;
    return (x * (3 + b));
}

int Un(int n, int b) {
    return (2*b + 3);
}