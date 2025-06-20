#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define EMPTY_NODE -1

int binaryTreeArray[MAX_NODES];
int tree_max_index_used = -1;

void initializeTreeArray() {
    for (int i = 0; i < MAX_NODES; i++) {
        binaryTreeArray[i] = EMPTY_NODE;
    }
    tree_max_index_used = -1;
}

void createTreeArrayRecursive(int index) {
    if (index >= MAX_NODES) {
        return;
    }

    int data;
    printf("Enter data for node at index %d (-1 for no node): ", index);
    scanf("%d", &data);

    if (data == EMPTY_NODE) {
        binaryTreeArray[index] = EMPTY_NODE;
        return;
    }

    binaryTreeArray[index] = data;
    if (index > tree_max_index_used) {
        tree_max_index_used = index;
    }

    printf("--- For left child of %d (index %d) ---\n", data, index);
    createTreeArrayRecursive(2 * index + 1);

    printf("--- For right child of %d (index %d) ---\n", data, index);
    createTreeArrayRecursive(2 * index + 2);
}

void preorderTraversalArray(int index) {
    if (index > tree_max_index_used || binaryTreeArray[index] == EMPTY_NODE) {
        return;
    }
    printf("%d ", binaryTreeArray[index]);
    preorderTraversalArray(2 * index + 1);
    preorderTraversalArray(2 * index + 2);
}

void inorderTraversalArray(int index) {
    if (index > tree_max_index_used || binaryTreeArray[index] == EMPTY_NODE) {
        return;
    }
    inorderTraversalArray(2 * index + 1);
    printf("%d ", binaryTreeArray[index]);
    inorderTraversalArray(2 * index + 2);
}

void postorderTraversalArray(int index) {
    if (index > tree_max_index_used || binaryTreeArray[index] == EMPTY_NODE) {
        return;
    }
    postorderTraversalArray(2 * index + 1);
    postorderTraversalArray(2 * index + 2);
    printf("%d ", binaryTreeArray[index]);
}

int main() {
    int choice;

    initializeTreeArray();

    do {
        printf("\n--- Binary Tree (Array Representation) Menu ---\n");
        printf("1. Create Tree\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeTreeArray();
                printf("Starting tree creation. Enter -1 for no node.\n");
                createTreeArrayRecursive(0);
                printf("Tree creation complete.\n");
                break;

            case 2:
                if (tree_max_index_used == -1 || binaryTreeArray[0] == EMPTY_NODE) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorderTraversalArray(0);
                    printf("\n");
                }
                break;

            case 3:
                if (tree_max_index_used == -1 || binaryTreeArray[0] == EMPTY_NODE) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorderTraversalArray(0);
                    printf("\n");
                }
                break;

            case 4:
                if (tree_max_index_used == -1 || binaryTreeArray[0] == EMPTY_NODE) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Postorder Traversal: ");
                    postorderTraversalArray(0);
                    printf("\n");
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

