#include <iostream>
#include <cmath>
using namespace std; 
  
int findMin(int arr[], int n, int sum);
  
int main(void)
{
    int T;
    cin >> T;

    int arr[T];
    int tmp;
    int sum = 0;

    for (int i = 0; i < T; i++) {
        cin >> tmp;
        sum += tmp;
        arr[i] = tmp;
    }

    int half = findMin(arr, T, sum);
    int other = abs(sum - half);

    if (half > other) {
        cout << half << " " << other << endl;
    }
    else {
        cout << other << " " << half << endl;
    }

    return 0;
}

int findMin(int arr[], int n, int sum) 
{ 
    bool **dp = new bool*[n+1];
    for (int i = 0; i < n+1; i++) {
        dp[i] = new bool[sum+1];
    }
  
    for (int i = 0; i <= n; i++) 
        dp[i][0] = true; 
  
    for (int i = 1; i <= sum; i++) 
        dp[0][i] = false; 
  
    for (int i = 1; i <= n; i++) 
    { 
        for (int j = 1; j <= sum; j++) 
        { 
            // If i'th element is excluded 
            dp[i][j] = dp[i-1][j]; 
  
            // If i'th element is included 
            if (arr[i-1] <= j) 
                dp[i][j] |= dp[i-1][j-arr[i-1]]; 
        } 
    } 
   
    for (int j=sum/2; j>=0; j--) 
    { 
        // Find the  
        if (dp[n][j] == true) 
        {
            for (int i = 0; i < n+1; i++) {
                delete[] dp[i];
            }
            delete[] dp;
            return j;
        } 
    } 
    return 1; 
} 