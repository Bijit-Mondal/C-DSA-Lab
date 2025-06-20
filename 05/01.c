#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* createTree() {
    int data;
    printf("Enter node data (-1 for no node): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    Node* newNode = createNode(data);
    printf("Enter left child of %d:\n", data);
    newNode->left = createTree();

    printf("Enter right child of %d:\n", data);
    newNode->right = createTree();

    return newNode;
}

void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
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
    int choice;

    do {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Create Tree\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root != NULL) {
                    freeTree(root);
                    root = NULL;
                }
                root = createTree();
                printf("Tree created.\n");
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorderTraversal(root);
                    printf("\n");
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Inorder Traversal: ");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty. Please create a tree first.\n");
                } else {
                    printf("Postorder Traversal: ");
                    postorderTraversal(root);
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

    freeTree(root);
    return 0;
}

