#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void swapNodes(Node** head_ref, Node* prev_a, Node* a, Node* prev_b, Node* b) {
    if (a == NULL || b == NULL || a == b) return;

    if (prev_a != NULL) {
        prev_a->next = b;
    } else {
        *head_ref = b;
    }

    if (prev_b != NULL) {
        prev_b->next = a;
    } else {
        *head_ref = a;
    }

    Node* temp = a->next;
    a->next = b->next;
    b->next = temp;
}

void bubbleSortLinkedListByLinks(Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    Node *prev_ptr1;

    do {
        swapped = 0;
        prev_ptr1 = NULL;
        ptr1 = *head_ref;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                Node* next_node = ptr1->next;
                if (prev_ptr1 != NULL) {
                    prev_ptr1->next = next_node;
                } else {
                    *head_ref = next_node;
                }
                ptr1->next = next_node->next;
                next_node->next = ptr1;
                swapped = 1;

                prev_ptr1 = next_node;
            } else {
                prev_ptr1 = ptr1;
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}

void insertionSortLinkedListByLinks(Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    Node* sorted = NULL;
    Node* current = *head_ref;

    while (current != NULL) {
        Node* next_node = current->next;
        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next_node;
    }
    *head_ref = sorted;
}

void selectionSortLinkedListByLinks(Node** head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    Node* current = *head_ref;
    Node* tail = NULL;

    while (current->next != tail) {
        Node* min_prev = NULL;
        Node* min_node = current;
        Node* prev = current;
        Node* temp = current->next;

        while (temp != tail) {
            if (temp->data < min_node->data) {
                min_node = temp;
                min_prev = prev;
            }
            prev = temp;
            temp = temp->next;
        }

        if (min_node != current) {
            if (min_prev != NULL) {
                min_prev->next = min_node->next;
            } else {
                *head_ref = min_node->next;
            }

            min_node->next = current;

            if (current == *head_ref) {
                 *head_ref = min_node;
            } else {
                Node* find_prev_current = *head_ref;
                while(find_prev_current != NULL && find_prev_current->next != current) {
                    find_prev_current = find_prev_current->next;
                }
                if(find_prev_current != NULL) {
                    find_prev_current->next = min_node;
                }
            }
            current = min_node;
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
        printf("\n--- Sorting Techniques (Linked List - Interchanging Links) ---\n");
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
                bubbleSortLinkedListByLinks(&current_list_head);
                printf("List after Bubble Sort (by links): ");
                displayList(current_list_head);
                break;

            case 2:
                insertionSortLinkedListByLinks(&current_list_head);
                printf("List after Insertion Sort (by links): ");
                displayList(current_list_head);
                break;

            case 3:
                selectionSortLinkedListByLinks(&current_list_head);
                printf("List after Selection Sort (by links): ");
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
