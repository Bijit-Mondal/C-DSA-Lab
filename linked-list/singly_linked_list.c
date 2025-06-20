#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INVALID_POSITION -1
#define SUCCESS 0

typedef struct node{
    int info;
    struct node *link;
}Node;

Node *start = NULL;

Node *createnode(){
    Node *t;
    t = (Node *)malloc(sizeof(Node));
    return(t);
}

int insert(int pos, int d){
    if(pos < 1) return INVALID_POSITION;
    Node *new = createnode();
    if (new == NULL) {
        printf("\nMemory allocation failed!");
        return INVALID_POSITION;
    }
    new->info = d;
    new->link = NULL;

    if(pos == 1){
        new->link = start;
        start = new;
        return SUCCESS;
    }

    Node *pre = start;
    int idx = 1;
    
    while(pre != NULL && idx<pos - 1){
        pre = pre->link;
        idx++;
    }

    if(pre == NULL){
        printf("\nInvalid position %d for insertion.", pos);
        free(new); 
        return INVALID_POSITION;
    }
    new->link = pre->link;
    pre->link = new;
    return SUCCESS;
}

int insertAtEnd(int data){
    Node *new = createnode();
    if(new == NULL){
        printf("\nMemory allocation failed!");
        return INVALID_POSITION;
    }
    new->info = data;
    new->link = NULL;
    if(start == NULL){
        start = new;
    }else{
        Node *p = start;
        while(p->link != NULL){
            p = p->link;
        }
        p->link = new;
    }
    return SUCCESS;
}

int insertAfterValue(int data,int key){
    Node *new = createnode();
    if(new == NULL){
        printf("\nMemory allocation failed!");
        free(new);
        return INVALID_POSITION;
    }
    new->info = data;
    new->link = NULL;
    if(start == NULL){
        printf("\nList is empty, cannot insert after value.");
        free(new);
        return INVALID_POSITION;
    }
    Node *p = start;
    while(p != NULL && p->info != key){
        p = p->link;
    }
    if(p == NULL){
        printf("\nValue %d not found in the list!", key);
        free(new);
        return INVALID_POSITION;
    }
    new->link = p->link;
    p->link = new;
    return SUCCESS;
}

// Function to insert node before the first node containing 'key'
// Returns SUCCESS (0) on success, INVALID_POSITION (-1) if key not found or list empty.
int insertBeforeValue(int data,int key){
    Node *new = createnode();
     if (new == NULL) {
        printf("\nMemory allocation failed!");
        free(new);
        return INVALID_POSITION; // Indicate failure
    }
    new->info = data;
    new->link = NULL;
    if(start == NULL){
        printf("\nList is empty, cannot insert before value.");
        free(new);
        return INVALID_POSITION;
    }

    // Case 1: Insert before the head node
    if(start->info == key){
        new->link = start;
        start = new;
        return SUCCESS;
    }

    // Case 2: Insert before a node other than the head
    Node *p = start;
    Node *q = NULL; // q trails p
    while(p != NULL && p->info != key){
        q = p;
        p = p->link;
    }

    // Check if the key was found
    if(p == NULL){ // Key not found
        printf("\nValue %d not found in the list!", key);
        free(new);
        return INVALID_POSITION;
    }

    // Insert the new node between q and p
    assert(q != NULL); // Should not be NULL if p is not the start node
    q->link = new;
    new->link = p;
    return SUCCESS;
}

// Function to delete the node at position 'pos' (1-based index)
// Handles deletion at beginning (pos=1), end, and specific positions.
// Returns SUCCESS (0) on success, INVALID_POSITION (-1) on failure.
int deletion(int pos){
    if(pos < 1 || start == NULL){
        printf("\nList is empty or invalid position %d for deletion.", pos);
        return INVALID_POSITION;
    }

    Node *nodeToDelete = NULL;
    Node *prev = NULL;

    if(pos == 1){
        nodeToDelete = start;
        start = start->link;
    }
    else{
        prev = start;
        int idx = 1;
        while(prev != NULL && idx < pos - 1){
            prev = prev->link;
            idx++;
        }

        if(prev == NULL || prev->link == NULL){
            printf("\nPosition %d not found for deletion!", pos);
            return INVALID_POSITION;
        }

        nodeToDelete = prev->link;
        prev->link = nodeToDelete->link;
    }

    if (nodeToDelete != NULL) {
        printf("\nDeleted node with value: %d", nodeToDelete->info);
        free(nodeToDelete);
    }

    return SUCCESS;
}

int deleteLastNode() {
    if (start == NULL) {
        printf("\nList is empty, cannot delete last node.");
        return INVALID_POSITION;
    }

    Node *toDelete = NULL;
    if (start->link == NULL) {
        toDelete = start;
        start = NULL;
    }
    else{
        Node *secondLast = start;
        while (secondLast->link != NULL && secondLast->link->link != NULL) {
            secondLast = secondLast->link;
        }
        toDelete = secondLast->link;
        secondLast->link = NULL;
    }

    if (toDelete != NULL) {
         printf("\nDeleted last node with value: %d", toDelete->info);
        free(toDelete);
    }
    return SUCCESS;
}

int deleteValue(int key){
    if(start == NULL){
        printf("\nList is empty, cannot delete value.");
        return INVALID_POSITION;
    }

    Node *p = start;
    Node *q = NULL;

    if(p->info == key){
        start = p->link;
        printf("\nDeleted node with value: %d", p->info);
        free(p);
        return SUCCESS;
    }

    q = p;
    p = p->link;
    while(p != NULL){
        if(p->info == key){
            q->link = p->link;
            printf("\nDeleted node with value: %d", p->info);
            free(p);
            return SUCCESS;
        }
        q = p;
        p = p->link;
    }

    printf("\nValue %d not found for deletion!", key);
    return INVALID_POSITION;
}

int deleteList(){
    Node *current = start;
    Node *nextNode = NULL;
    if(start == NULL) {
        printf("\nList is already empty.");
        return SUCCESS;
    }

    printf("\nDeleting entire list...");
    while(current != NULL){
        nextNode = current->link;
        printf("\nDeleting node with value %d", current->info);
        free(current);
        current = nextNode;
    }
    start = NULL;
    printf("\nList deleted successfully.");
    return SUCCESS;
}

int reverseList() {
    if (start == NULL || start->link == NULL) {
        printf("\nList is empty or has only one node.");
        return SUCCESS;
    }

    Node *prev = NULL;
    Node *current = start;
    Node *nextNode = NULL;

    while(current != NULL){
        nextNode = current->link;
        current->link = prev;
        prev = current;
        current = nextNode;
    }
    start = prev;
    printf("\nList reversed successfully.");
    return SUCCESS;
}

// Function to sort the linked list using bubble sort (ascending order)
int sortList() {
    if (start == NULL || start->link == NULL) {
        printf("\nList is empty or has only one node, already sorted.");
        return SUCCESS;
    }
    
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = start;
        
        while (ptr1->link != lptr) {
            if (ptr1->info > ptr1->link->info) {
                // Swap data
                int temp = ptr1->info;
                ptr1->info = ptr1->link->info;
                ptr1->link->info = temp;
                swapped = 1;
            }
            ptr1 = ptr1->link;
        }
        lptr = ptr1;
    } while (swapped);
    
    printf("\nList sorted successfully.");
    return SUCCESS;
}

// Function to search for a value in the list
// Returns position (1-based) if found, 0 if not found
int searchElement(int key) {
    if (start == NULL) {
        printf("\nList is empty, cannot search.");
        return 0;
    }
    
    Node *current = start;
    int position = 1;
    
    while (current != NULL) {
        if (current->info == key) {
            printf("\nElement %d found at position %d.", key, position);
            return position;
        }
        current = current->link;
        position++;
    }
    
    printf("\nElement %d not found in the list.", key);
    return 0;
}

// Function to create a new list (for merging and concatenation operations)
Node* createNewList() {
    Node* newStart = NULL;
    int n, data;
    
    printf("\nEnter number of elements for the new list: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &data);
        
        Node* new = createnode();
        if (new == NULL) {
            printf("\nMemory allocation failed!");
            continue;
        }
        
        new->info = data;
        new->link = NULL;
        
        if (newStart == NULL) {
            newStart = new;
        } else {
            Node* temp = newStart;
            while (temp->link != NULL) {
                temp = temp->link;
            }
            temp->link = new;
        }
    }
    
    return newStart;
}

// Function to merge two sorted lists
int mergeLists() {
    printf("\nCreating first sorted list...");
    Node* list1 = start;
    
    printf("\nCreating second sorted list...");
    Node* list2 = createNewList();
    
    // Sort both lists if they aren't already sorted
    if (list1 != NULL) {
        // Sort the first list
        int swapped;
        Node *ptr1;
        Node *lptr = NULL;
        
        do {
            swapped = 0;
            ptr1 = list1;
            
            while (ptr1->link != lptr) {
                if (ptr1->info > ptr1->link->info) {
                    int temp = ptr1->info;
                    ptr1->info = ptr1->link->info;
                    ptr1->link->info = temp;
                    swapped = 1;
                }
                ptr1 = ptr1->link;
            }
            lptr = ptr1;
        } while (swapped);
    }
    
    if (list2 != NULL) {
        // Sort the second list
        int swapped;
        Node *ptr1;
        Node *lptr = NULL;
        
        do {
            swapped = 0;
            ptr1 = list2;
            
            while (ptr1->link != lptr) {
                if (ptr1->info > ptr1->link->info) {
                    int temp = ptr1->info;
                    ptr1->info = ptr1->link->info;
                    ptr1->link->info = temp;
                    swapped = 1;
                }
                ptr1 = ptr1->link;
            }
            lptr = ptr1;
        } while (swapped);
    }
    
    // Handle empty list cases
    if (list1 == NULL) {
        start = list2;
        return SUCCESS;
    }
    if (list2 == NULL) {
        return SUCCESS; // First list remains unchanged
    }
    
    // Create a dummy node to simplify merging
    Node dummy;
    Node* tail = &dummy;
    dummy.link = NULL;
    
    // Merge the two sorted lists
    while (list1 != NULL && list2 != NULL) {
        if (list1->info <= list2->info) {
            tail->link = list1;
            list1 = list1->link;
        } else {
            tail->link = list2;
            list2 = list2->link;
        }
        tail = tail->link;
    }
    
    // Attach remaining nodes
    if (list1 != NULL) {
        tail->link = list1;
    } else {
        tail->link = list2;
    }
    
    // Update start pointer
    start = dummy.link;
    
    printf("\nLists merged successfully.");
    return SUCCESS;
}

// Function to concatenate two lists
int concatenateLists() {
    printf("\nCreating list to concatenate...");
    Node* list2 = createNewList();
    
    if (start == NULL) {
        start = list2;
        printf("\nLists concatenated successfully.");
        return SUCCESS;
    }
    
    if (list2 == NULL) {
        printf("\nSecond list is empty, nothing to concatenate.");
        return SUCCESS;
    }
    
    // Find the end of the first list
    Node* temp = start;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    
    // Connect the end of first list to the start of second list
    temp->link = list2;
    
    printf("\nLists concatenated successfully.");
    return SUCCESS;
}

// Function to check if two lists are equal
int areListsEqual() {
    printf("\nCreating second list to compare...");
    Node* list2 = createNewList();
    
    Node* p1 = start;
    Node* p2 = list2;
    
    // Compare each node
    while (p1 != NULL && p2 != NULL) {
        if (p1->info != p2->info) {
            printf("\nLists are not equal.");
            
            // Free the second list to avoid memory leaks
            while (list2 != NULL) {
                Node* temp = list2;
                list2 = list2->link;
                free(temp);
            }
            
            return 0; // Not equal
        }
        p1 = p1->link;
        p2 = p2->link;
    }
    
    // If one list is longer than the other
    if (p1 != NULL || p2 != NULL) {
        printf("\nLists are not equal (different lengths).");
        
        // Free the second list to avoid memory leaks
        while (list2 != NULL) {
            Node* temp = list2;
            list2 = list2->link;
            free(temp);
        }
        
        return 0; // Not equal
    }
    
    printf("\nLists are equal.");
    
    // Free the second list to avoid memory leaks
    while (list2 != NULL) {
        Node* temp = list2;
        list2 = list2->link;
        free(temp);
    }
    
    return 1; // Equal
}

void viewlist(){
    Node *p;
    if(start == NULL){
        printf("\nList is empty.");
    }
    else{
        printf("\nCurrent List: ");
        p = start;
        while(p != NULL){
            printf("%d -> ", p->info);
            p = p->link;
        }
        printf("NULL\n");
    }
}

static void test(){
    printf("\n--- Running Self-Tests ---");
    // Clear list initially
    deleteList();
    assert(start == NULL);

    // Test Insertions
    assert(insert(1, 10) == SUCCESS); // Insert front (now using insert)
    assert(start != NULL && start->info == 10 && start->link == NULL);
    viewlist(); // Expected: 10 -> NULL
    assert(insertAtEnd(20) == SUCCESS);
    assert(start->link != NULL && start->link->info == 20 && start->link->link == NULL);
    viewlist(); // Expected: 10 -> 20 -> NULL
    assert(insert(2, 15) == SUCCESS); // Insert at pos 2
    assert(start->link != NULL && start->link->info == 15 && start->link->link->info == 20);
    viewlist(); // Expected: 10 -> 15 -> 20 -> NULL
    assert(insert(1, 5) == SUCCESS); // Insert front again
    assert(start->info == 5 && start->link->info == 10);
    viewlist(); // Expected: 5 -> 10 -> 15 -> 20 -> NULL
    assert(insert(5, 25) == SUCCESS); // Insert at end (pos 5)
    viewlist(); // Expected: 5 -> 10 -> 15 -> 20 -> 25 -> NULL
    assert(insert(7, 30) == INVALID_POSITION); // Invalid position
    assert(insert(0, 30) == INVALID_POSITION); // Invalid position
    assert(insertAfterValue(18, 15) == SUCCESS);
    viewlist(); // Expected: 5 -> 10 -> 15 -> 18 -> 20 -> 25 -> NULL
    assert(insertAfterValue(19, 99) == INVALID_POSITION); // Value not found
    assert(insertBeforeValue(12, 15) == SUCCESS);
    viewlist(); // Expected: 5 -> 10 -> 12 -> 15 -> 18 -> 20 -> 25 -> NULL
    assert(insertBeforeValue(2, 5) == SUCCESS); // Insert before head
    viewlist(); // Expected: 2 -> 5 -> 10 -> 12 -> 15 -> 18 -> 20 -> 25 -> NULL
    assert(insertBeforeValue(21, 99) == INVALID_POSITION); // Value not found

    // Test Deletions
    assert(deletion(1) == SUCCESS); // Delete first (2)
    assert(start->info == 5);
    viewlist(); // Expected: 5 -> 10 -> 12 -> 15 -> 18 -> 20 -> 25 -> NULL
    assert(deletion(0) == INVALID_POSITION); // Invalid position
    assert(deletion(10) == INVALID_POSITION); // Invalid position (out of bounds)
    assert(deleteLastNode() == SUCCESS); // Delete last (25)
    viewlist(); // Expected: 5 -> 10 -> 12 -> 15 -> 18 -> 20 -> NULL
    assert(deletion(3) == SUCCESS); // Delete kth (12)
    viewlist(); // Expected: 5 -> 10 -> 15 -> 18 -> 20 -> NULL
    assert(deleteValue(18) == SUCCESS); // Delete value
    viewlist(); // Expected: 5 -> 10 -> 15 -> 20 -> NULL
    assert(deleteValue(99) == INVALID_POSITION); // Value not found
    assert(deletion(2) == SUCCESS); // Delete 10 (delete before 3rd node - 15) -> Now list is 5 -> 15 -> 20 -> NULL
    viewlist(); // Expected: 5 -> 15 -> 20 -> NULL
    assert(deletion(3) == SUCCESS); // Delete 20 (delete after 2nd node - 15) -> Now list is 5 -> 15 -> NULL
    viewlist(); // Expected: 5 -> 15 -> NULL

    // Test Reverse
    assert(reverseList() == SUCCESS);
    viewlist(); // Expected: 15 -> 5 -> NULL
    assert(start->info == 15 && start->link->info == 5 && start->link->link == NULL);
    assert(reverseList() == SUCCESS); // Reverse back
    viewlist(); // Expected: 5 -> 15 -> NULL
    assert(start->info == 5 && start->link->info == 15 && start->link->link == NULL);

    // Test Delete Last on two nodes
    assert(deleteLastNode() == SUCCESS); // Deletes 15
    viewlist(); // Expected: 5 -> NULL
    assert(start->info == 5 && start->link == NULL);

    // Test Reverse on one node
    assert(reverseList() == SUCCESS); // No change expected
    viewlist(); // Expected: 5 -> NULL
    assert(start->info == 5 && start->link == NULL);

     // Test Delete Last on one node
    assert(deleteLastNode() == SUCCESS); // Deletes 5
    viewlist(); // Expected: List is empty.
    assert(start == NULL);

     // Test operations on empty list
    assert(deletion(1) == INVALID_POSITION);
    assert(deleteLastNode() == INVALID_POSITION);
    assert(deleteValue(10) == INVALID_POSITION);
    assert(reverseList() == SUCCESS); // Should succeed without error on empty list
    assert(insertAfterValue(10, 5) == INVALID_POSITION);
    assert(insertBeforeValue(10, 5) == INVALID_POSITION);

    // Test Delete List
    insert(1, 1); insert(2, 2); insert(3, 3);
    viewlist(); // Expected: 1 -> 2 -> 3 -> NULL
    assert(deleteList() == SUCCESS);
    assert(start == NULL);
    viewlist(); // Expected: List is empty.
    printf("\n--- Self-Tests Successfully Passed! ---\n");
}

void menu(){
    printf("\n----- Singly Linked List Operations -----");
    printf("\n 1. Print List Content");
    printf("\n 2. Insert at Front");
    printf("\n 3. Insert at End");
    printf("\n 4. Insert After K-th Node");
    printf("\n 5. Insert After Value");
    printf("\n 6. Insert Before K-th Node");
    printf("\n 7. Insert Before Value");
    printf("\n 8. Delete First Node");
    printf("\n 9. Delete Last Node");
    printf("\n10. Delete After K-th Node");
    printf("\n11. Delete Before K-th Node");
    printf("\n12. Delete K-th Node");
    printf("\n13. Delete Node with Specified Value");
    printf("\n14. Reverse List");
    printf("\n15. Delete Entire List");
    printf("\n16. Sort the List");
    printf("\n17. Search for an Element");
    printf("\n18. Merge Two Sorted Lists");
    printf("\n19. Concatenate Two Lists");
    printf("\n20. Check if Two Lists are Equal");
    printf("\n21. Exit");
    printf("\n-----------------------------------------");
    printf("\nEnter your choice: ");
}

int main(){
    int choice = 0, data = 0, k = 0, value = 0, status = 0;

    printf("\nSelect Mode:");
    printf("\n1. Self Test Mode");
    printf("\n2. Manual Mode");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1){
        test();
    }
    else if(choice == 2){
        while(1){
            menu();
            scanf("%d", &choice);
            status = INVALID_POSITION;

            switch(choice){
                case 1:
                    viewlist();
                    status = SUCCESS;
                    break;
                case 2:
                    printf("Enter data to insert at front: ");
                    scanf("%d", &data);
                    status = insert(1, data);
                    break;
                case 3:
                    printf("Enter data to insert at end: ");
                    scanf("%d", &data);
                    status = insertAtEnd(data);
                    break;
                case 4:
                    printf("Enter position (k) after which to insert: ");
                    scanf("%d", &k);
                    printf("Enter data to insert: ");
                    scanf("%d", &data);
                    status = insert(k + 1, data);
                    break;
                case 5:
                    printf("Enter value after which to insert: ");
                    scanf("%d", &value);
                    printf("Enter data to insert: ");
                    scanf("%d", &data);
                    status = insertAfterValue(data, value);
                    break;
                case 6:
                    printf("Enter position (k) before which to insert: ");
                    scanf("%d", &k);
                    printf("Enter data to insert: ");
                    scanf("%d", &data);
                    status = insert(k, data);
                    break;
                case 7:
                    printf("Enter value before which to insert: ");
                    scanf("%d", &value);
                    printf("Enter data to insert: ");
                    scanf("%d", &data);
                    status = insertBeforeValue(data, value);
                    break;
                case 8:
                    status = deletion(1);
                    break;
                case 9:
                    status = deleteLastNode();
                    break;
                case 10:
                    printf("Enter position (k) after which to delete: ");
                    scanf("%d", &k);
                    if(k < 0){
                         printf("Invalid position k=%d. k must be >= 0.", k);
                         status = INVALID_POSITION;
                     } else {
                         status = deletion(k + 1);
                     }
                    break;
                case 11:
                    printf("Enter position (k) before which to delete: ");
                    scanf("%d", &k);
                    if(k <= 1){
                        printf("Cannot delete node before position %d.", k);
                        status = INVALID_POSITION;
                    } else {
                        status = deletion(k - 1);
                    }
                    break;
                case 12:
                    printf("Enter position (k) to delete: ");
                    scanf("%d", &k);
                    status = deletion(k);
                    break;
                case 13:
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    status = deleteValue(value);
                    break;
                case 14:
                    status = reverseList();
                    break;
                case 15:
                    status = deleteList();
                    break;
                case 16:
                    status = sortList();
                    break;
                case 17:
                    printf("Enter element to search: ");
                    scanf("%d", &value);
                    status = (searchElement(value) > 0) ? SUCCESS : INVALID_POSITION;
                    break;
                case 18:
                    status = mergeLists();
                    break;
                case 19:
                    status = concatenateLists();
                    break;
                case 20:
                    status = areListsEqual() ? SUCCESS : INVALID_POSITION;
                    break;
                case 21:
                    printf("Exiting program.\n");
                    deleteList();
                    exit(0);
                default:
                    printf("\nInvalid choice. Please try again.");
                    status = SUCCESS;
            }

            if(status == SUCCESS && choice >= 2 && choice <= 20){
                 printf("\nOperation successful.");
                 viewlist();
            } else if (status == INVALID_POSITION) {
                 printf("\nOperation failed or position/value invalid.");
            }
            printf("\n");
        }
    }
    else{
        printf("Invalid mode choice. Exiting.\n");
    }
    return 0;
}