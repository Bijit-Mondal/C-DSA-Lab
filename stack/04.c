#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

bool are_stacks_equal(int stack_id1, int stack_id2)
{
    int size1 = size(stack_id1);
    int size2 = size(stack_id2);

    if (size1 != size2)
    {
        return false;
    }

    int *stack1_elements = (int *)malloc(size1 * sizeof(int));
    int *stack2_elements = (int *)malloc(size2 * sizeof(int));

    if (stack1_elements == NULL || stack2_elements == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }

    for (int i = size1 - 1; i >= 0; i--)
    {
        int *data = (int *)pop(stack_id1);
        stack1_elements[i] = *data;
    }

    for (int i = 0; i < size1; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = stack1_elements[i];
        push(stack_id1, data);
    }

    for (int i = size2 - 1; i >= 0; i--)
    {
        int *data = (int *)pop(stack_id2);
        stack2_elements[i] = *data;
    }

    for (int i = 0; i < size2; i++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = stack2_elements[i];
        push(stack_id2, data);
    }

    for (int i = 0; i < size1; i++)
    {
        if (stack1_elements[i] != stack2_elements[i])
        {
            free(stack1_elements);
            free(stack2_elements);
            return false;
        }
    }

    free(stack1_elements);
    free(stack2_elements);
    return true;
}

int main()
{
    int num_stacks = 2;
    init_stack(num_stacks);

    int a = 10, b = 20, c = 10, d = 20;

    push(0, &a);
    push(0, &b);
    push(1, &c);
    push(1, &d);

    bool equal = are_stacks_equal(0, 1);
    printf("Are stacks equal? %s\n", equal ? "true" : "false");

    return 0;
}
