// #include "Flib/utility.h"

#ifndef UTILITY_H
#define UTILITY_H

// #include <sys/resource.h>

// Prototypes
void isi(int *arr, int n); // Isi array
void IrandArr(int *arr, int n, int max); // Random array (int)
void SrandArr(char *arr, int len);
void swap(int *a, int *b); // Swap pointer
void IprintArr(int arr[], int n); // Print array

// double calculate(const struct rusage *b, const struct rusage *a); // Hitung running-time dari fungsi

#endif // UTILITY_H already defined

/* Panduan penggunaan fungsi calculate
#include <sys/resource.h>
#include <sys/time.h>
struct rusage before, after;

getrusage(RUSAGE_SELF, &before);
load(dictionary);
getrusage(RUSAGE_SELF, &after);

double time_load = calculate(&before, &after);
print("%lf\n", time_load);
*/