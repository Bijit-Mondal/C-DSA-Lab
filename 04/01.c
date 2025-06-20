#include <stdio.h>

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

void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int linearSearchIterative(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int linearSearchRecursiveHelper(int arr[], int index, int size, int target) {
    if (index >= size) {
        return -1;
    }
    if (arr[index] == target) {
        return index;
    }
    return linearSearchRecursiveHelper(arr, index + 1, size, target);
}

int linearSearchRecursive(int arr[], int size, int target) {
    return linearSearchRecursiveHelper(arr, 0, size, target);
}


int binarySearchIterative(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int binarySearchRecursive(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2; // To prevent potential overflow

    if (arr[mid] == target) {
        return mid;
    }
    else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, high, target);
    }
    else { // arr[mid] > target
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
}


int main() {
    int arr[100]; // Declare a fixed-size array
    int size = 0;
    int choice, target, result;

    printf("Enter the number of elements for the array (max 100): ");
    scanf("%d", &size);

    if (size <= 0 || size > 100) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    printf("Enter %d integer elements:\n", size);
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    do {
        printf("\n--- Searching Techniques Menu ---\n");
        printf("1. Linear Search (Iterative)\n");
        printf("2. Linear Search (Recursive)\n");
        printf("3. Binary Search (Iterative)\n");
        printf("4. Binary Search (Recursive)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &target);
                result = linearSearchIterative(arr, size, target);
                if (result != -1) {
                    printf("Element %d found at index %d (Iterative Linear Search).\n", target, result);
                } else {
                    printf("Element %d not found (Iterative Linear Search).\n", target);
                }
                break;

            case 2:
                printf("Enter the element to search: ");
                scanf("%d", &target);
                result = linearSearchRecursive(arr, size, target);
                if (result != -1) {
                    printf("Element %d found at index %d (Recursive Linear Search).\n", target, result);
                } else {
                    printf("Element %d not found (Recursive Linear Search).\n", target);
                }
                break;

            case 3:
                printf("\n--- IMPORTANT: Binary Search requires a SORTED array. ---\n");
                printf("Sorting the current array for Binary Search...\n");
                sortArray(arr, size);
                printArray(arr, size);
                printf("Enter the element to search: ");
                scanf("%d", &target);
                result = binarySearchIterative(arr, size, target);
                if (result != -1) {
                    printf("Element %d found at index %d (Iterative Binary Search).\n", target, result);
                } else {
                    printf("Element %d not found (Iterative Binary Search).\n", target);
                }
                break;

            case 4:
                printf("\n--- IMPORTANT: Binary Search requires a SORTED array. ---\n");
                printf("Sorting the current array for Binary Search...\n");
                sortArray(arr, size);
                printArray(arr, size);
                printf("Enter the element to search: ");
                scanf("%d", &target);
                result = binarySearchRecursive(arr, 0, size - 1, target);
                if (result != -1) {
                    printf("Element %d found at index %d (Recursive Binary Search).\n", target, result);
                } else {
                    printf("Element %d not found (Recursive Binary Search).\n", target);
                }
                break;

            case 5:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}

