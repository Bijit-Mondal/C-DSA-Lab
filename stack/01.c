#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"

void menu()
{
    printf("\n=== Stack Operations Menu ===\n");
    printf("a. Push\n");
    printf("b. Pop\n");
    printf("c. Display Stack\n");
    printf("d. Get Stack Size\n");
    printf("e. Check if Stack is Empty\n");
    printf("f. Get Top Element\n");
    printf("q. Quit\n");
    printf("Enter your choice: ");
}

int main()
{
    int stack_id = 0;
    int num_stacks = 1;
    init_stack(num_stacks);
    char choice;
    while (1)
    {
        menu();
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a':
            int *data = (int *)malloc(sizeof(int));
            if (data == NULL)
            {
                printf("Memory allocation failed\n");
                break;
            }
            printf("Enter data: ");
            scanf("%d", data);
            push(stack_id, data);
            break;
        case 'b':
            void *popped = pop(stack_id);
            if (popped != NULL)
            {
                printf("Popped element: %d\n", *(int *)popped);
                free(popped);
            }
            break;
        case 'c':
            display_int_stack(stack_id);
            break;
        case 'd':
            printf("Stack size: %d\n", size(stack_id));
            break;
        case 'e':
            printf("Stack is empty: %s\n", isEmpty(stack_id) ? "Yes" : "No");
            break;
        case 'f':
            void *topElement = top(stack_id);
            if (topElement != NULL)
            {
                printf("Top element: %d\n", *(int *)topElement);
            }
            break;
        case 'q':
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}