// https://www.hackerrank.com/contests/final-sd-2020/challenges/train-of-thought

#include <iostream>
#include <cstring>
using namespace std;

const int maxSize = 100000000;

int main(void)
{
    bool *arr = new bool[maxSize];
    memset(arr, false, sizeof(bool) * maxSize);

    int N;
    cin >> N;

    while (N-- > 0) {
        int input;
        cin >> input;

        // Input is duplicate
        if (arr[input - 1] == true) {
            cout << "SUSAH BANGED WOI!" << endl;
            return 0;
        } 
        else {
            arr[input - 1] = true;
        }
    }
    cout << "NAH GITU DONG, NGEGAS!" << endl;
    return 0;
}
