// #include "Flib/sorter.h"

#ifndef SORTER_H
#define SORTER_H

//Prototype
int medianOf3(int *arr, int e, int f, int g); // cari index nilai rata dari 3 sampel
int quickSelect(int *a, int n, int k); // Cara angka ke-'k' yang terbesar/terkecil (0 sampai n-1)
int partition(int *a, int lo, int hi);

void ModinsertionSort(int *a, int lo, int hi);
void quick3Sort(int *a, int n); // Anti-duplicate key
void quickSort(int *a, int n); // Quick sort = divide and conquer (faster) (in-place) (unstable) (less memory)
void mergeSort(int *a, int n); // Merge sort = divide and conquer (slower) (external) (stable) (more memory)

void knuthShuffle(int *a, int n); // Knuth Shuffle = Shuffle array

void Op_shellSort(int *a, int n); // OP Shell sort versi Sedgewick (fastest)
void shellSort(int *a, int n); // Shell sort = Insertion sort dengan gap
void insertionSort(int *a, int n); // Insertion sort = tukar a[i] dgn yg lebih besar di kirinya
void selectionSort(int *a, int n);  // Selection sort = cari nilai terkecil, lalu taruh di depan
void bubbleSort(int *a, int n); // Bubble Sort = tukar array yang berbatasan

#endif // SORTER_H already defined