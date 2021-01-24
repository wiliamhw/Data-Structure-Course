/* Modul0, no.2
* Membuat dynamic array dgn fungsi
* 1. dArray_insertAt = masukin nilai di indeks tertentu
* 2. dArray_removeAt = hapus elemen tertentu
* MENYIMPAN INT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DynamicArray
{
    int *arr;
    unsigned int size, capacity;
} DynamicArray;

void randomAdd(DynamicArray *dArray); // RNG
void dArray_pushBack(DynamicArray *dArray, int num); // Masukin angka di tail
void dArray_insertAt(DynamicArray *dArray, unsigned int index, int value); // Masukin angka di index tertentu
void dArray_removeAt(DynamicArray *dArray, unsigned int index); // Hapus angka di index tertentu
void dArray_printAll(DynamicArray dArray); // Print semua angka di dArray

#define d_pushBack dArray_pushBack
#define d_printAll dArray_printAll
#define d_iat dArray_insertAt
#define d_rat dArray_removeAt

/* Command: pb  = pushback
*           iat = insert at
*           rat = remove at
*/

int main(void)
{
    DynamicArray dArray;

    // Initialize dArray
    dArray.size = 0;
    dArray.capacity = 2;
    dArray.arr = (int*) malloc(sizeof(int) * 2);

    // Isi Dynamic Array
    int value;
    unsigned int index;
    char *command = malloc(sizeof(char) * 4);
    while (1)
    {
        // Get command
        printf("Command: ");
        scanf("%s", command);

        if (strcmp(command, (char*) "pb") == 0) // Push back
        {
            while (1)
            {
                printf("Input: ");
                if (!scanf("%d", &value)) break;

                if(value == 0) randomAdd(&dArray);
                else d_pushBack(&dArray, value);
            }
        }
        else if (strcmp(command, "iat") == 0) // Insert at
        {
            printf("Input <index> <value> => ");
            scanf("%u %d", &index, &value);

            d_iat(&dArray, index, value);
        }
        else if (strcmp(command, "rat") == 0) // Remove at
        {
            printf("Remove <index> => ");
            scanf("%u", &index);

            d_rat(&dArray, index);
        }
        else if (strcmp(command, "print") == 0)
            d_printAll(dArray);

        else break;
        getchar();
        printf("\n");
    }

    d_printAll(dArray);
    free(command);
    free(dArray.arr);
    return 0;
}

void dArray_removeAt(DynamicArray *dArray, unsigned int index)
{
    if (index >= dArray->size)
    {
        index = dArray->size - 1;
    }
    dArray->size--;

    int *tmp = (int*) realloc(dArray->arr, sizeof(int) * dArray->capacity);

    for (int i = index + 1; i <= dArray->size; i++)
    {
        tmp[i - 1] = dArray->arr[i];
        // printf("%d<>%d ", tmp[i - 1], dArray->arr[i]);
    }
    // printf("\nINDEX: %d\n", tmp[index]);
    // printf("\n");
    dArray->arr = tmp;

    return;
}

void dArray_insertAt(DynamicArray *dArray, unsigned int index, int value)
{
    if (index >= dArray->size)
    {
       d_pushBack(dArray, value);
    }
    else
    {
        // If dArray is full
        if (++dArray->size == dArray->capacity)
        {
            // Allocate space
            dArray->capacity *= 2;
        }
        int *tmp = (int*) realloc(dArray->arr, sizeof(int) * dArray->capacity);

        // Masukan angka di index
        tmp[index] = value;
        // printf("\n%d\n", tmp[index]);

        for (int i = index + 1; i < dArray->size; i++)
        {
            tmp[i] = dArray->arr[i - 1];
            // printf("%d<>%d ", tmp[i], dArray->arr[i]);
        }
        // printf("\n");
        dArray->arr = tmp;
    }
    return;
}

void dArray_printAll(DynamicArray dArray)
{
    printf("Isi array: ");
    for (int i = 0; i < dArray.size; i++)
    {
        printf("%d ", dArray.arr[i]);
    }
    printf("\n");
    return;
}

void dArray_pushBack(DynamicArray *dArray, int value)
{
    // If dArray is full
    if (dArray->size == dArray->capacity)
    {
        // Allocate space
        dArray->capacity *= 2;
        dArray->arr = (int*) realloc(dArray->arr, sizeof(int) * dArray->capacity);
    }

    // Add number
    dArray->arr[dArray->size++] = value;
    return;
}

void randomAdd(DynamicArray *dArray)
{
    srand(time(NULL));

    // Maks 10 item
    int loop = rand() % 10 + 1;
    printf("Random Input: ");

    for (int i = 0; i < loop; i++)
    {
        // Angka maks = 100
        int num = rand() % 99 + 1;
        printf("%d ", num);
        d_pushBack(dArray, num);
    }

    printf("\n");
    return;
}