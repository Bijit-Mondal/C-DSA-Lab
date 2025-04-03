#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carray.h"

void displayMenu() {
    printf("\n=== Array Operations Menu ===\n");
    printf("a. Create a new array\n");
    printf("b. Display the array\n");
    printf("c. Count elements\n");
    printf("d. Reverse the array\n");
    printf("e. Find index of an element\n");
    printf("f. Get element at index\n");
    printf("g. Insert an element\n");
    printf("h. Delete an element\n");
    printf("i. Merge with another array\n");
    printf("j. Split the array\n");
    printf("k. Sort the array\n");
    printf("q. Quit\n");
    printf("Enter your choice: ");
}

CArray* mergeArrays(CArray* arr1, CArray* arr2) {
    CArray* result = getCArray(arr1->size + arr2->size);
    int i;
    
    for (i = 0; i < arr1->size; i++) {
        result->array[i] = arr1->array[i];
    }
    
    for (i = 0; i < arr2->size; i++) {
        result->array[arr1->size + i] = arr2->array[i];
    }
    
    return result;
}

void splitArray(CArray* original, CArray** first, CArray** second, int position) {
    if (position <= 0 || position >= original->size) {
        printf("Invalid split position!\n");
        return;
    }
    
    *first = getCArray(position);
    *second = getCArray(original->size - position);
    
    int i;
    for (i = 0; i < position; i++) {
        (*first)->array[i] = original->array[i];
    }
    
    for (i = position; i < original->size; i++) {
        (*second)->array[i - position] = original->array[i];
    }
}

int CArrayTests() {
    CArray* array = NULL;
    CArray* tempArray = NULL;
    CArray* firstArray = NULL;
    CArray* secondArray = NULL;
    char choice;
    int size, position, value, index, splitPos;
    int sortChoice;
    
    do {
        displayMenu();
        scanf(" %c", &choice);
        
        switch (choice) {
            case 'a': // Create
                printf("Enter the size of the array: ");
                scanf("%d", &size);
                if (array != NULL) {
                    free(array->array);
                    free(array);
                }
                array = getCArray(size);
                printf("Enter %d elements: ", size);
                for (int i = 0; i < size; i++) {
                    scanf("%d", &value);
                    array->array[i] = value;
                }
                printf("Array created successfully!\n");
                break;
                
            case 'b': // Display
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    displayCArray(array);
                }
                break;
                
            case 'c': // Count
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Total number of elements: %d\n", array->size);
                }
                break;
                
            case 'd': // Reverse
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    reverseCArray(array);
                    printf("Array reversed successfully!\n");
                    displayCArray(array);
                }
                break;
                
            case 'e': // Index of an element
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Enter the element to find: ");
                    scanf("%d", &value);
                    CArray* positions = valuePositionsCArray(array, value);
                    if (positions->size == 0) {
                        printf("Element %d not found in the array.\n", value);
                    } else {
                        printf("Element %d found at positions: ", value);
                        for (int i = 0; i < positions->size; i++) {
                            printf("%d ", positions->array[i]);
                        }
                        printf("\n");
                    }
                    free(positions->array);
                    free(positions);
                }
                break;
                
            case 'f': // Element at index
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Enter the index: ");
                    scanf("%d", &index);
                    if (index < 0 || index >= array->size) {
                        printf("Invalid index!\n");
                    } else {
                        printf("Element at index %d is %d\n", index, array->array[index]);
                    }
                }
                break;
                
            case 'g': // Insert
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Enter the position to insert: ");
                    scanf("%d", &position);
                    printf("Enter the value to insert: ");
                    scanf("%d", &value);
                    if (insertValueCArray(array, position, value) == SUCCESS) {
                        printf("Element inserted successfully!\n");
                        displayCArray(array);
                    } else {
                        printf("Failed to insert element. Invalid position!\n");
                    }
                }
                break;
                
            case 'h': // Delete
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Enter the position to delete: ");
                    scanf("%d", &position);
                    if (removeValueCArray(array, position) == SUCCESS) {
                        printf("Element deleted successfully!\n");
                        displayCArray(array);
                    } else {
                        printf("Failed to delete element. Invalid position!\n");
                    }
                }
                break;
                
            case 'i': // Merge
                if (array == NULL) {
                    printf("First array not created yet!\n");
                } else {
                    printf("Enter the size of the second array: ");
                    scanf("%d", &size);
                    tempArray = getCArray(size);
                    printf("Enter %d elements for the second array: ", size);
                    for (int i = 0; i < size; i++) {
                        scanf("%d", &value);
                        tempArray->array[i] = value;
                    }
                    CArray* mergedArray = mergeArrays(array, tempArray);
                    free(array->array);
                    free(array);
                    free(tempArray->array);
                    free(tempArray);
                    array = mergedArray;
                    printf("Arrays merged successfully!\n");
                    displayCArray(array);
                }
                break;
                
            case 'j': // Split
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Enter the position to split the array: ");
                    scanf("%d", &splitPos);
                    if (splitPos <= 0 || splitPos >= array->size) {
                        printf("Invalid split position!\n");
                    } else {
                        splitArray(array, &firstArray, &secondArray, splitPos);
                        printf("First part after split: ");
                        displayCArray(firstArray);
                        printf("Second part after split: ");
                        displayCArray(secondArray);
                        
                        printf("Which part do you want to keep? (1/2): ");
                        int keepChoice;
                        scanf("%d", &keepChoice);
                        
                        if (keepChoice == 1) {
                            free(array->array);
                            free(array);
                            free(secondArray->array);
                            free(secondArray);
                            array = firstArray;
                            printf("First part kept.\n");
                        } else if (keepChoice == 2) {
                            free(array->array);
                            free(array);
                            free(firstArray->array);
                            free(firstArray);
                            array = secondArray;
                            printf("Second part kept.\n");
                        } else {
                            printf("Invalid choice, keeping original array.\n");
                            free(firstArray->array);
                            free(firstArray);
                            free(secondArray->array);
                            free(secondArray);
                        }
                    }
                }
                break;
                
            case 'k': // Sort
                if (array == NULL) {
                    printf("Array not created yet!\n");
                } else {
                    printf("Choose sorting algorithm:\n");
                    printf("1. Bubble Sort\n");
                    printf("2. Selection Sort\n");
                    printf("3. Insertion Sort\n");
                    printf("4. Random Shuffle (Blender)\n");
                    printf("Enter choice: ");
                    scanf("%d", &sortChoice);
                    
                    switch (sortChoice) {
                        case 1:
                            bubbleSortCArray(array);
                            printf("Array sorted using Bubble Sort.\n");
                            break;
                        case 2:
                            selectionSortCArray(array);
                            printf("Array sorted using Selection Sort.\n");
                            break;
                        case 3:
                            insertionSortCArray(array);
                            printf("Array sorted using Insertion Sort.\n");
                            break;
                        case 4:
                            blenderCArray(array);
                            printf("Array randomly shuffled.\n");
                            break;
                        default:
                            printf("Invalid sorting choice.\n");
                    }
                    displayCArray(array);
                }
                break;
                
            case 'q': // Quit
                printf("Exiting program...\n");
                if (array != NULL) {
                    free(array->array);
                    free(array);
                }
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while (choice != 'q');
    
    return 0;
}

int main() {
    CArrayTests();
    return 0;
}