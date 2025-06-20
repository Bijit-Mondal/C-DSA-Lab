#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int isLeftThread;  // 1 if left pointer is a thread, 0 if child
    int isRightThread; // 1 if right pointer is a thread, 0 if child
} Node;

Node* inorder_prev = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isLeftThread = 0;
    newNode->isRightThread = 0;
    return newNode;
}

Node* createStandardBinaryTree() {
    int data;
    printf("Enter node data (-1 for no node): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    Node* newNode = createNode(data);
    printf("Enter left child of %d:\n", data);
    newNode->left = createStandardBinaryTree();

    printf("Enter right child of %d:\n", data);
    newNode->right = createStandardBinaryTree();

    return newNode;
}

void convertToInorderThreadedRecursive(Node* root) {
    if (root == NULL) {
        return;
    }

    convertToInorderThreadedRecursive(root->left);

    if (root->left == NULL) {
        root->left = inorder_prev;
        root->isLeftThread = 1;
    }

    if (inorder_prev != NULL && inorder_prev->right == NULL) {
        inorder_prev->right = root;
        inorder_prev->isRightThread = 1;
    }

    inorder_prev = root;

    convertToInorderThreadedRecursive(root->right);
}

void convertToInorderThreaded(Node* root) {
    inorder_prev = NULL; // Reset global prev pointer for each conversion
    convertToInorderThreadedRecursive(root);
}



Node* leftmost(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    while (node->isLeftThread == 0 && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Inorder traversal using threads (non-recursive)
void inorderTraversalThreaded(Node* root) {
    if (root == NULL) {
        printf("Tree is empty or not threaded.\n");
        return;
    }

    Node* current = leftmost(root);

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->isRightThread == 1) {
            current = current->right;
        }
        else {
            current = leftmost(current->right);
        }
    }
    printf("\n");
}

void preorderTraversalThreaded(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    if (root->isLeftThread == 0) { // Only recurse if it's a child pointer
        preorderTraversalThreaded(root->left);
    }
    if (root->isRightThread == 0) { // Only recurse if it's a child pointer
        preorderTraversalThreaded(root->right);
    }
}

void postorderTraversalThreaded(Node* root) {
    if (root == NULL) {
        return;
    }
    if (root->isLeftThread == 0) {
        postorderTraversalThreaded(root->left);
    }
    if (root->isRightThread == 0) {
        postorderTraversalThreaded(root->right);
    }
    printf("%d ", root->data);
}

void freeTreeThreaded(Node* root) {
    if (root == NULL) {
        return;
    }
    // Only recurse on actual children, not threads
    if (root->isLeftThread == 0) {
        freeTreeThreaded(root->left);
    }
    if (root->isRightThread == 0) {
        freeTreeThreaded(root->right);
    }
    free(root);
}

int main() {
    Node* root = NULL;
    int choice;
    int is_threaded = 0; // Flag to check if the tree has been threaded

    do {
        printf("\n--- Threaded Binary Tree (Inorder) Menu ---\n");
        printf("1. Create Standard Binary Tree\n");
        printf("2. Convert to Inorder Threaded Tree\n");
        printf("3. Preorder Traversal (Threaded Tree)\n");
        printf("4. Inorder Traversal (Threaded Tree)\n");
        printf("5. Postorder Traversal (Threaded Tree)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root != NULL) {
                    freeTreeThreaded(root); // Free existing tree if any
                    root = NULL;
                    is_threaded = 0;
                }
                printf("Creating a standard binary tree:\n");
                root = createStandardBinaryTree();
                printf("Standard tree created. Remember to convert it to threaded.\n");
                break;

            case 2:
                if (root == NULL) {
                    printf("Please create a standard binary tree first (Option 1).\n");
                } else if (is_threaded) {
                    printf("Tree is already threaded.\n");
                } else {
                    convertToInorderThreaded(root);
                    is_threaded = 1;
                    printf("Tree successfully converted to Inorder Threaded Binary Tree.\n");
                }
                break;

            case 3:
                if (root == NULL || !is_threaded) {
                    printf("Tree is empty or not threaded. Please create and thread the tree first.\n");
                } else {
                    printf("Preorder Traversal: ");
                    preorderTraversalThreaded(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL || !is_threaded) {
                    printf("Tree is empty or not threaded. Please create and thread the tree first.\n");
                } else {
                    printf("Inorder Traversal (using threads): ");
                    inorderTraversalThreaded(root);
                }
                break;

            case 5:
                if (root == NULL || !is_threaded) {
                    printf("Tree is empty or not threaded. Please create and thread the tree first.\n");
                } else {
                    printf("Postorder Traversal: ");
                    postorderTraversalThreaded(root);
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

    if (root != NULL) {
        freeTreeThreaded(root);
    }
    return 0;
}

