#include <stdlib.h>
#include <time.h>
#include "utility.h"
#include "sorter.h"

#define mCUTTOF 7
#define qCUTTOF 10

int quickSelect(int *a, int n, int k)
{
    knuthShuffle(a, n);
    int lo = 0;
    int hi = n - 1;

    while (hi > lo)
    {
        int j = partition(a, lo, hi);
        if      (k > j) lo = j + 1;
        else if (k < j) hi = j - 1;
        else            return a[k];
    }

    return a[k];
}

///////////////////// 3 Way Quicksort//////////////////////////////////
void Pquick3S(int *a, int lo, int hi)
{
    if (hi <= lo) return;

    // Optimisasi 1 = insertion sort jika item <= 10
    int item = hi - lo + 1;
    if (item < qCUTTOF)
    {
        ModinsertionSort(a, lo, hi);
        return;
    }
    // Optimisasi 2 = median of 3 jika item > 10
    else
    {
        int m = medianOf3(a, lo, lo + (hi - lo)/2, hi);
        swap(&a[lo], &a[m]);
    }

    int lt = lo;
    int gt = hi;
    int v = a[lo];
    int i = lo;

    while (i <= gt)
    {
        if      (a[i] < v)  swap(&a[i++], &a[lt++]);
        else if (a[i] > v)  swap(&a[i], &a[gt--]);
        else                i++;
    }

    Pquick3S(a, lo, lt - 1);
    Pquick3S(a, gt + 1, hi);

    return;
}

void quick3Sort(int *a, int n)
{
    knuthShuffle(a, n);
    Pquick3S(a, 0, n - 1);
    return;
}

//////////////////////// Quick Sort ///////////////////////////////////
int partition(int *a, int lo, int hi)
{
    int i = lo;
    int j = hi + 1;

    while (1 == 1)
    {
        while (a[++i] < a[lo])  // COMPARE
            if (i == hi) break;

        while (a[lo] < a[--j]) // COMPARE
            if (j == lo) break;

        if (i >= j) break;
        swap(&a[i], &a[j]);
    }

    swap(&a[j], &a[lo]);
    return j;
}

void Pquick_sort(int *a, int lo, int hi)
{
    if (hi <= lo) return;

    // Optimisasi 1 = insertion sort jika item <= 10
    int item = hi - lo + 1;
    if (item < qCUTTOF)
    {
        ModinsertionSort(a, lo, hi);
        return;
    }
    // Optimisasi 2 = median of 3 jika item > 10
    else
    {
        int m = medianOf3(a, lo, lo + (hi - lo)/2, hi);
        swap(&a[lo], &a[m]);
    }

    int j = partition(a, lo, hi);
    Pquick_sort(a, lo, j - 1);
    Pquick_sort(a, j + 1, hi);
}

void quickSort(int *a, int n)
{
    knuthShuffle(a, n);
    Pquick_sort(a, 0, n - 1);
    return;
}

//////////////////////// Merge Sort //////////////////////////////
void merge(int *a, int *aux, int lo, int mid, int hi)
{
    // Copy
    for (int k = lo; k <= hi; k++)
    {
        aux[k] = a[k];
    }

    // Merge
    int i = lo;
    int j = mid + 1;
    for (int k = lo; k <= hi; k++)
    {
        if      (i > mid)           a[k] = aux[j++];    // COMPARE
        else if (j > hi)            a[k] = aux[i++];    // COMPARE
        else if (aux[j] < aux[i])   a[k] = aux[j++];    // COMPARE
        else                        a[k] = aux[i++];
    }
}

void Pmerge_sort(int *a, int *aux, int lo, int hi)
{
    if (hi <= lo) return;

    // Optimisasi 1 = insertion sort jika item <= 7
    int item = hi - lo + 1;
    if (item <= mCUTTOF)
    {
        ModinsertionSort(a, lo, hi);
        return;
    }

    int mid = lo + (hi - lo) / 2;
    Pmerge_sort(a, aux, lo, mid);
    Pmerge_sort(a, aux, mid + 1, hi);

    // Optimisasi 2
    if (a[mid] < a[mid + 1]) return;    // COMPARE
    merge(a, aux, lo, mid, hi);
}

void mergeSort(int *a, int n)
{
    int aux[n];
    Pmerge_sort(a, aux, 0, n - 1);
    return;
}
///////////////////////////////////////////////////////////

void knuthShuffle(int *a, int n)
{
    srand(time(NULL));
    for (int i = 1; i < n; i++)
    {
        int r = rand() % (i + 1);
        swap(&a[i], &a[r]);
    }
}

void Op_shellSort(int *a, int n)
{
    const int incs[] = {
        1, 3, 7, 21, 48, 112,
        336, 861, 1968, 4592, 13776,
        33936, 86961, 198768, 463792, 1391376,
        3402672, 8382192, 21479367, 49095696, 114556624,
        343669872, 52913488, 2085837936};

    int index = 0;
    while (incs[index + 1] < n) index++;

    while (index >= 0)
    {
        int gap = incs[index];
        for (int i = gap; i < n; i++)
        {
            for (int j = i; j >= gap && a[j] < a[j - gap]; j -= gap) // COMPARE
            {
                swap(&a[j], &a[j - gap]);
            }
        }
        index--;
    }
    return;
}

void shellSort(int *a, int n)
{
    int gap = 1;
    while (gap < n/3) gap = 3*gap + 1;

    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            for (int j = i; j >= gap && a[j] < a[j - gap]; j -= gap) // COMPARE
            {
                swap(&a[j], &a[j - gap]);
            }
        }
        gap /= 3;
    }
    return;
}

void ModinsertionSort(int *a, int lo, int hi)
{
    for (int i = lo + 1; i <= hi; i++)
    {
        for (int j = i; j > lo; j--)
        {
            if (a[j] < a[j - 1]) swap(&a[j], &a[j - 1]); // COMPARE
            else break;
        }
    }
    return;
}

void insertionSort(int *a, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (a[j] < a[j - 1]) swap(&a[j], &a[j - 1]); // COMPARE
            else break;
        }
    }
    return;
}

void selectionSort(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min]) min = j;
        }
        swap(&a[i], &a[min]);
    }
    return;
}

void bubbleSort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j + 1] < a[j]) swap(&a[j], &a[j + 1]);
        }
    }
    return;
}

int medianOf3(int *arr, int e, int f, int g)
{
    int a = arr[e];
    int b = arr[f];
    int c = arr[g];

    if ((a <= b) && (b <= c)) return f;  // a b c
    if ((a <= c) && (c <= b)) return g;  // a c b
    if ((b <= a) && (a <= c)) return e;  // b a c
    if ((b <= c) && (c <= a)) return g;  // b c a
    if ((c <= a) && (a <= b)) return e;  // c a b
    return f;                            // c b a
}