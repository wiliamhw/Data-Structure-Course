/* Modul0, no.2
* Membuat dynamic array dgn fungsi
* 1. dArray_insertAt = masukin nilai di indeks tertentu
* 2. dArray_removeAt = hapus elemen tertentu
* MENYIMPAN STRING
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGHT 101
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef struct DynamicArray
{
    char *string;
    unsigned int size, capacity;
} DynamicArray;

void randomAdd(DynamicArray *dArray); // RNG
void dArray_pushBack(DynamicArray *dArray, char *word); // Masukin angka di tail
void dArray_insertAt(DynamicArray *dArray, unsigned int index, char *word); // Masukin angka di index tertentu
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
    dArray.capacity = 2*LENGHT;
    dArray.string = (char*) malloc(sizeof(char) * dArray.capacity);

    // Isi Dynamic Array
    char *word = (char*) malloc(sizeof(char) * LENGHT);
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
                scanf("%s", word);
                if (strcmp(word, "s") == 0) break;

                if (strcmp(word, "0") == 0) randomAdd(&dArray);
                else d_pushBack(&dArray, word);
            }
        }
        else if (strcmp(command, "iat") == 0) // Insert at
        {
            printf("Input <index> <word> => ");
            scanf("%u %s", &index, word);

            d_iat(&dArray, index*LENGHT, word);
        }
        else if (strcmp(command, "rat") == 0) // Remove at
        {
            printf("Remove <index> => ");
            scanf("%d", &index);

            d_rat(&dArray, index*LENGHT);
        }
        else if (strcmp(command, "print") == 0)
            d_printAll(dArray);

        else break;
        getchar();
        printf("\n");
    }

    d_printAll(dArray);
    free(word);
    free(command);
    free(dArray.string);
    return 0;
}

void dArray_removeAt(DynamicArray *dArray, unsigned int index)
{
    if (index >= dArray->size)
    {
        index = dArray->size - LENGHT;
    }
    dArray->size -= LENGHT;

    char *tmp = (char*) realloc(dArray->string, sizeof(char) * dArray->capacity);

    for (int i = index + LENGHT; i <= dArray->size; i += LENGHT)
    {
        strcpy(&tmp[i - LENGHT], &dArray->string[i]);
    }
    dArray->string = tmp;

    return;
}

void dArray_insertAt(DynamicArray *dArray, unsigned int index, char *word)
{
    if (index >= dArray->size)
    {
       d_pushBack(dArray, word);
    }
    else
    {
        // If dArray is full
        dArray->size += LENGHT;
        if (dArray->size == dArray->capacity)
        {
            // Allocate space
            dArray->capacity *= 2;
        }
        char *tmp = (char*) realloc(dArray->string, sizeof(char) * dArray->capacity);

        strcpy(&tmp[index], word);
        // printf("\n%s\n", &tmp[index]);

        for (int i = index + LENGHT; i < dArray->size; i += LENGHT)
        {
            strcpy(&tmp[i], &dArray->string[i - LENGHT]);
            // printf("%s ", &tmp[i]);
        }
        // printf("\n");
        dArray->string = tmp;
    }
    return;
}

void dArray_printAll(DynamicArray dArray)
{
    printf("Isi array: ");
    for (int i = 0; i < dArray.size; i += LENGHT)
    {
        printf("%s ", &dArray.string[i]);
    }
    printf("\n");
    return;
}

void dArray_pushBack(DynamicArray *dArray, char *word)
{
    // If dArray is full
    if (dArray->size == dArray->capacity)
    {
        // Allocate space
        dArray->capacity *= 2;
        char *str = (char*) realloc(dArray->string, sizeof(char) * dArray->capacity);
        dArray->string = str;
    }

    // Add number
    strcpy(&dArray->string[dArray->size], word);
    dArray->size += LENGHT;
    return;
}

void randomAdd(DynamicArray *dArray)
{
    srand(time(NULL));

    int kata = rand() % 8 + 3; // Maks 10 kata, min 3 kata

    printf("Random Word: ");
    for (int i = 0; i < kata; i++)
    {
        int len = rand() % 8 + 3; // Maks 10 huruf, min 3 huruf per kata

        char randString[len + 1];
        for (int j = 0; j < len; j++)
        {
            int key = rand() % (int) (sizeof(charset) - 1);
            randString[j] = charset[key];
        }
        randString[len] = '\0';

        printf("%s ", randString);

        d_pushBack(dArray, randString);
    }

    printf("\n");
    return;
}