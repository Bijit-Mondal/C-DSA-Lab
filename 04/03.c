#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    printf("List elements: [");
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* copyList(Node* original_head) {
    if (original_head == NULL) {
        return NULL;
    }
    Node* new_head = NULL;
    Node* original_temp = original_head;
    while (original_temp != NULL) {
        insertAtEnd(&new_head, original_temp->data);
        original_temp = original_temp->next;
    }
    return new_head;
}

void bubbleSortLinkedList(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void insertionSortLinkedList(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node *current = head->next;
    while (current != NULL) {
        Node *walker = head;
        while (walker != current) {
            if (walker->data > current->data) {
                int temp = walker->data;
                walker->data = current->data;
                current->data = temp;
            }
            walker = walker->next;
        }
        current = current->next;
    }
}

void selectionSortLinkedList(Node* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node *current = head;
    Node *min_node;
    Node *walker;

    while (current->next != NULL) {
        min_node = current;
        walker = current->next;
        while (walker != NULL) {
            if (walker->data < min_node->data) {
                min_node = walker;
            }
            walker = walker->next;
        }
        if (min_node != current) {
            int temp = current->data;
            current->data = min_node->data;
            min_node->data = temp;
        }
        current = current->next;
    }
}

int main() {
    Node* original_list_head = NULL;
    Node* current_list_head = NULL;
    int num_elements;
    int data;
    int choice;

    printf("Enter the number of elements for the linked list: ");
    scanf("%d", &num_elements);

    if (num_elements <= 0) {
        printf("Invalid number of elements. Exiting.\n");
        return 1;
    }

    printf("Enter %d integer elements:\n", num_elements);
    for (int i = 0; i < num_elements; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &data);
        insertAtEnd(&original_list_head, data);
    }

    do {
        printf("\n--- Sorting Techniques (Linked List - Interchanging Data) ---\n");
        printf("Original List: ");
        displayList(original_list_head);
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            current_list_head = copyList(original_list_head);
            printf("List before sorting: ");
            displayList(current_list_head);
        }

        switch (choice) {
            case 1:
                bubbleSortLinkedList(current_list_head);
                printf("List after Bubble Sort: ");
                displayList(current_list_head);
                break;

            case 2:
                insertionSortLinkedList(current_list_head);
                printf("List after Insertion Sort: ");
                displayList(current_list_head);
                break;

            case 3:
                selectionSortLinkedList(current_list_head);
                printf("List after Selection Sort: ");
                displayList(current_list_head);
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
        if (choice >= 1 && choice <= 3) {
            freeList(current_list_head);
            current_list_head = NULL;
        }
    } while (choice != 4);

    freeList(original_list_head);
    return 0;
}

