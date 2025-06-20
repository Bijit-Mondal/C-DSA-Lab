#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

Node* findMin(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    int choice, data;
    Node* resultNode;

    do {
        printf("\n--- Binary Search Tree Menu ---\n");
        printf("1. Create/Initialize Tree (by inserting first element)\n");
        printf("2. Insert Element\n");
        printf("3. Search Element\n");
        printf("4. Delete Element\n");
        printf("5. Display Inorder Traversal (for verification)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("Tree already exists. Clearing existing tree...\n");
                    freeTree(root);
                    root = NULL;
                }
                printf("Enter the root element: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Tree created with root %d.\n", data);
                break;

            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Element %d inserted.\n", data);
                break;

            case 3:
                printf("Enter element to search: ");
                scanf("%d", &data);
                resultNode = search(root, data);
                if (resultNode != NULL) {
                    printf("Element %d found in the BST.\n", data);
                } else {
                    printf("Element %d not found in the BST.\n", data);
                }
                break;

            case 4:
                printf("Enter element to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Deletion process for %d completed (check traversal to verify).\n", data);
                break;

            case 5:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;

            case 6:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    freeTree(root); // Free all allocated memory before exiting
    return 0;
}

