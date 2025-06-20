#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int arr[], int size) {
    printf("Array elements: [");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void bubbleSort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size) {
    int i, j, min_idx, temp;
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int original_arr[100];
    int current_arr[100];
    int size = 0;
    int choice;

    printf("Enter the number of elements for the array (max 100): ");
    scanf("%d", &size);

    if (size <= 0 || size > 100) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    printf("Enter %d integer elements:\n", size);
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &original_arr[i]);
    }

    do {
        memcpy(current_arr, original_arr, size * sizeof(int));

        printf("\n--- Sorting Techniques Menu ---\n");
        printf("Original Array: ");
        printArray(original_arr, size);
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Array before sorting: ");
                printArray(current_arr, size);
                bubbleSort(current_arr, size);
                printf("Array after Bubble Sort: ");
                printArray(current_arr, size);
                break;

            case 2:
                printf("Array before sorting: ");
                printArray(current_arr, size);
                insertionSort(current_arr, size);
                printf("Array after Insertion Sort: ");
                printArray(current_arr, size);
                break;

            case 3:
                printf("Array before sorting: ");
                printArray(current_arr, size);
                selectionSort(current_arr, size);
                printf("Array after Selection Sort: ");
                printArray(current_arr, size);
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

