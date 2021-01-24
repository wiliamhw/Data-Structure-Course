/**
 * Implementasi ADT Dynamic Array
 *
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 *
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LENGHT 100

// Struktur ADT DynamicArray

typedef struct dynamicarr_t {
    char *string;
    unsigned _size, _capacity;
} DynamicArray;

// Prototipe fungsi

void dArray_init(DynamicArray *darray);
bool dArray_isEmpty(DynamicArray *darray);
void dArray_pushBack(DynamicArray *darray, char string[LENGHT + 1]);
void dArray_popBack(DynamicArray *darray);
char *dArray_back(DynamicArray *darray);
char *dArray_front(DynamicArray *darray);
void dArray_setAt(DynamicArray *darray, unsigned index, char string[LENGHT + 1]);
char *dArray_getAt(DynamicArray *darray, unsigned index);

// Definisi fungsi

void dArray_init(DynamicArray *darray)
{
    darray->_capacity = 2*(LENGHT + 1);
    darray->_size = 0u;
    darray->string = (char*) malloc(sizeof(char) * darray->_capacity);
}

bool dArray_isEmpty(DynamicArray *darray) {
    return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, char string[LENGHT + 1])
{
    if (darray->_size + 1 > darray->_capacity) {
        darray->_capacity *= 2;
        darray->string = (char*) realloc(darray->string, sizeof(char) * 2 * darray->_capacity);
    }
    strcpy(&darray->string[darray->_size], string);
    darray->_size += LENGHT + 1;
}

void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size -= (LENGHT + 1);
    else return;
}

char *dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return &darray->string[darray->_size-(LENGHT + 1)];
    else return 0;
}

char *dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return &darray->string[0];
    else return 0;
}

void dArray_setAt(
    DynamicArray *darray, unsigned index, char string[LENGHT + 1])
{
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            strcpy(&darray->string[darray->_size-(LENGHT + 1)], string);
        else
            strcpy(&darray->string[index], string);
    }
}

char *dArray_getAt(DynamicArray *darray, unsigned index)
{
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return &darray->string[darray->_size-(LENGHT + 1)];
        else
            return &darray->string[index];
    }
    return 0;
}

/* Gunakan ini untuk mempersingkat penulisan kode */

#define d_init dArray_init
#define d_isEmpty dArray_isEmpty
#define d_pushBack dArray_pushBack
#define d_popBack dArray_popBack
#define d_back dArray_back
#define d_front dArray_front
#define d_setAt dArray_setAt
#define d_getAt dArray_getAt

/* */

#include <stdio.h>

int main(void)
{
    // Buat objek DynamicArray
    DynamicArray myArray;

    // PENTING! Jangan lupa diinisialisasi
    dArray_init(&myArray);

    // Operasi-operasi
    // myArray => [11, 14, 17, 23]
    dArray_pushBack(&myArray, "1tes ");
    dArray_pushBack(&myArray, "2tes ");
    dArray_pushBack(&myArray, "3tes ");
    dArray_pushBack(&myArray, "4tes ");

    // isi myArray => [11, 14, 17]
    dArray_popBack(&myArray);

    int i = 0;
    while (i < myArray._size) {
        printf("%s ", dArray_getAt(&myArray, i));
        i += LENGHT + 1;
    }

    printf("\n");
    while (!dArray_isEmpty(&myArray)) {
        printf("%s ", dArray_back(&myArray));
        dArray_popBack(&myArray);
    }
    printf("\n");

    return 0;
}