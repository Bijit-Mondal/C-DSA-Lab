#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void createList() {
    head = NULL;
    printf("Empty list created\n");
}

void printList() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;
    printf("List: ");
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void insertFront(int data) {
    Node* newNode = createNode(data);

    if(head == NULL) {
        head = newNode;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void insertEnd(int data) {
    Node* newNode = createNode(data);

    if(head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAfterK(int k, int data) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;
    int count = 1;

    while(count < k && temp != NULL) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL) {
        printf("K exceeds list length\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next != NULL) {
        temp->next->prev = newNode;
    }

    temp->next = newNode;
}

void insertAfterValue(int value, int data) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;

    while(temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next != NULL) {
        temp->next->prev = newNode;
    }

    temp->next = newNode;
}

void insertBeforeK(int k, int data) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(k == 1) {
        insertFront(data);
        return;
    }

    Node* temp = head;
    int count = 1;

    while(count < k-1 && temp != NULL) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL || temp->next == NULL) {
        printf("K exceeds list length\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

void insertBeforeValue(int value, int data) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(head->data == value) {
        insertFront(data);
        return;
    }

    Node* temp = head;

    while(temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if(temp->next == NULL) {
        printf("Value not found\n");
        return;
    }

    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

void deleteFirst() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;
    head = head->next;

    if(head != NULL) {
        head->prev = NULL;
    }

    free(temp);
}

void deleteLast() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    free(temp);
}

void deleteAfterK(int k) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node* temp = head;
    int count = 1;

    while(count < k && temp != NULL) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL || temp->next == NULL) {
        printf("No node after K\n");
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;

    if(toDelete->next != NULL) {
        toDelete->next->prev = temp;
    }

    free(toDelete);
}

void deleteBeforeK(int k) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(k <= 1) {
        printf("No node before K\n");
        return;
    }

    if(k == 2) {
        deleteFirst();
        return;
    }

    Node* temp = head;
    int count = 1;

    while(count < k-2 && temp != NULL) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL || temp->next == NULL) {
        printf("K exceeds list length\n");
        return;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;

    if(toDelete->next != NULL) {
        toDelete->next->prev = temp;
    }

    free(toDelete);
}

void deleteK(int k) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(k == 1) {
        deleteFirst();
        return;
    }

    Node* temp = head;
    int count = 1;

    while(count < k && temp != NULL) {
        temp = temp->next;
        count++;
    }

    if(temp == NULL) {
        printf("K exceeds list length\n");
        return;
    }

    temp->prev->next = temp->next;

    if(temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

void deleteValue(int value) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }

    if(head->data == value) {
        deleteFirst();
        return;
    }

    Node* temp = head;

    while(temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Value not found\n");
        return;
    }

    temp->prev->next = temp->next;

    if(temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

void reverseList() {
    if(head == NULL || head->next == NULL) {
        return;
    }

    Node* current = head;
    Node* temp = NULL;

    while(current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(temp != NULL) {
        head = temp->prev;
    }
}

int main() {
    int choice, data, k, value;

    while(1) {
        printf("\n--- Doubly Linked List Operations ---\n");
        printf("1. Create a list\n");
        printf("2. Print list\n");
        printf("3. Insert at front\n");
        printf("4. Insert at end\n");
        printf("5. Insert after kth node\n");
        printf("6. Insert after value\n");
        printf("7. Insert before kth node\n");
        printf("8. Insert before value\n");
        printf("9. Delete first node\n");
        printf("10. Delete last node\n");
        printf("11. Delete after kth node\n");
        printf("12. Delete before kth node\n");
        printf("13. Delete kth node\n");
        printf("14. Delete node with value\n");
        printf("15. Reverse list\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                exit(0);
            case 1:
                createList();
                break;
            case 2:
                printList();
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                insertFront(data);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(data);
                break;
            case 5:
                printf("Enter k and data: ");
                scanf("%d %d", &k, &data);
                insertAfterK(k, data);
                break;
            case 6:
                printf("Enter value and data: ");
                scanf("%d %d", &value, &data);
                insertAfterValue(value, data);
                break;
            case 7:
                printf("Enter k and data: ");
                scanf("%d %d", &k, &data);
                insertBeforeK(k, data);
                break;
            case 8:
                printf("Enter value and data: ");
                scanf("%d %d", &value, &data);
                insertBeforeValue(value, data);
                break;
            case 9:
                deleteFirst();
                break;
            case 10:
                deleteLast();
                break;
            case 11:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteAfterK(k);
                break;
            case 12:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteBeforeK(k);
                break;
            case 13:
                printf("Enter k: ");
                scanf("%d", &k);
                deleteK(k);
                break;
            case 14:
                printf("Enter value: ");
                scanf("%d", &value);
                deleteValue(value);
                break;
            case 15:
                reverseList();
                printf("List reversed\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
