#include "carray.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CArray *getCArray(int size)
{
    CArray *array = (CArray *)malloc(sizeof(CArray));
    array->array = (int *)malloc(sizeof(int) * size);
    array->size = size;
    int i;
    for (i = 0; i < size; i++)
    {
        array->array[i] = 0;
    }
    return array;
}

CArray *getCopyCArray(CArray *array)
{
    CArray *copy = getCArray(array->size);
    int i;
    for (i = 0; i < array->size; i++)
    {
        copy->array[i] = array->array[i];
    }
    return copy;
}

int insertValueCArray(CArray *array, int position, int value)
{
    if (position < 0 || position > array->size)
        return INVALID_POSITION;
    
    int *newArray = (int *)malloc(sizeof(int) * (array->size + 1));
    int i;
    for (i = 0; i < position; i++)
    {
        newArray[i] = array->array[i];
    }
    newArray[position] = value;
    for (i = position; i < array->size; i++)
    {
        newArray[i + 1] = array->array[i];
    }
    
    free(array->array);
    array->array = newArray;
    array->size++;
    
    return SUCCESS;
}

int removeValueCArray(CArray *array, int position)
{
    if (position < 0 || position >= array->size)
        return INVALID_POSITION;
    
    int *newArray = (int *)malloc(sizeof(int) * (array->size - 1));
    int i;
    for (i = 0; i < position; i++)
    {
        newArray[i] = array->array[i];
    }
    for (i = position + 1; i < array->size; i++)
    {
        newArray[i - 1] = array->array[i];
    }
    
    free(array->array);
    array->array = newArray;
    array->size--;
    
    return SUCCESS;
}

int pushValueCArray(CArray *array, int value)
{
    return insertValueCArray(array, array->size, value);
}

int updateValueCArray(CArray *array, int position, int value)
{
    if (position < 0 || position >= array->size)
        return INVALID_POSITION;
    
    array->array[position] = value;
    return SUCCESS;
}

int eraseCArray(CArray *array)
{
    int i;
    for (i = 0; i < array->size; i++)
    {
        array->array[i] = ARRAY_ERASED;
    }
    return SUCCESS;
}

int switchValuesCArray(CArray *array, int position1, int position2)
{
    if (position1 < 0 || position1 >= array->size || 
        position2 < 0 || position2 >= array->size)
        return INVALID_POSITION;
    
    int temp = array->array[position1];
    array->array[position1] = array->array[position2];
    array->array[position2] = temp;
    
    return SUCCESS;
}

int reverseCArray(CArray *array)
{
    int i;
    for (i = 0; i < array->size / 2; i++)
    {
        switchValuesCArray(array, i, array->size - 1 - i);
    }
    return SUCCESS;
}

int bubbleSortCArray(CArray *array)
{
    int i, j;
    for (i = 0; i < array->size - 1; i++)
    {
        for (j = 0; j < array->size - i - 1; j++)
        {
            if (array->array[j] > array->array[j + 1])
            {
                switchValuesCArray(array, j, j + 1);
            }
        }
    }
    return SUCCESS;
}

int selectionSortCArray(CArray *array)
{
    int i, j, min_idx;
    for (i = 0; i < array->size - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < array->size; j++)
        {
            if (array->array[j] < array->array[min_idx])
            {
                min_idx = j;
            }
        }
        switchValuesCArray(array, i, min_idx);
    }
    return SUCCESS;
}

int insertionSortCArray(CArray *array)
{
    int i, j, key;
    for (i = 1; i < array->size; i++)
    {
        key = array->array[i];
        j = i - 1;

        while (j >= 0 && array->array[j] > key)
        {
            array->array[j + 1] = array->array[j];
            j = j - 1;
        }
        array->array[j + 1] = key;
    }
    return SUCCESS;
}

int blenderCArray(CArray *array)
{
    srand(time(NULL));
    int i;
    for (i = array->size - 1; i > 0; i--)
    {
        // Generate random index between 0 and i
        int j = rand() % (i + 1);
        // Swap array[i] and array[j]
        switchValuesCArray(array, i, j);
    }
    return SUCCESS;
}

int valueOcurranceCArray(CArray *array, int value)
{
    int count = 0;
    int i;
    for (i = 0; i < array->size; i++)
    {
        if (array->array[i] == value)
        {
            count++;
        }
    }
    return count;
}

CArray *valuePositionsCArray(CArray *array, int value)
{
    // First count occurrences to determine the size of result array
    int count = valueOcurranceCArray(array, value);
    CArray *positions = getCArray(count);
    
    if (count == 0)
    {
        return positions; // Return empty array if value not found
    }
    
    int posIndex = 0;
    int i;
    for (i = 0; i < array->size; i++)
    {
        if (array->array[i] == value)
        {
            positions->array[posIndex++] = i;
        }
    }
    
    return positions;
}

int findMaxCArray(CArray *array)
{
    if (array->size <= 0)
    {
        return ARRAY_ERASED; // Return error code if array is empty
    }
    
    int max = array->array[0];
    int i;
    for (i = 1; i < array->size; i++)
    {
        if (array->array[i] > max)
        {
            max = array->array[i];
        }
    }
    
    return max;
}

int findMinCArray(CArray *array)
{
    if (array->size <= 0)
    {
        return ARRAY_ERASED; // Return error code if array is empty
    }
    
    int min = array->array[0];
    int i;
    for (i = 1; i < array->size; i++)
    {
        if (array->array[i] < min)
        {
            min = array->array[i];
        }
    }
    
    return min;
}

int displayCArray(CArray *array)
{
    if (array == NULL || array->size <= 0)
    {
        printf("Empty array\n");
        return POSITION_EMPTY;
    }
    
    printf("Array [%d]: [ ", array->size);
    int i;
    for (i = 0; i < array->size; i++)
    {
        printf("%d ", array->array[i]);
    }
    printf("]\n");
    
    return SUCCESS;
}