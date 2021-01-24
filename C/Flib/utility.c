#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <sys/resource.h>

#include "utility.h"
#include "cs50.h"

// double calculate(const struct rusage *b, const struct rusage *a)
// {
//     if (b == NULL || a == NULL)
//     {
//         return 0.0;
//     }
//     else
//     {
//         return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
//                   (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
//                  ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
//                   (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
//                 / 1000000.0);
//     }
// }

void SrandArr(char *arr, int len)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	srand(time(NULL));

	int mod = len - 2;
    int ln = rand() % mod + 3; // Maks len huruf, min 3 huruf
    char randString[ln + 1];
    for (int j = 0; j < ln; j++)
    {
        int key = rand() % (int) (sizeof(charset) - 1);
        randString[j] = charset[key];
    }
    randString[ln] = '\0';
	strcpy(arr, randString);
	return;
}

void IrandArr(int *arr, int n, int max)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % (max + 1);
	}

    return;
}

void isi(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		// printf("Nilai arr ke-%d: ", i + 1);
		arr[i] = get_int("Nilai array ke-%d => ", i + 1);
	}
	return;
}

void IprintArr(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}