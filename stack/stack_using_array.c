// Write a program to implement a stack data structure using an array

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

typedef struct
{
    void **arr;
    uint64_t top_index;
    uint64_t size;
} Stack;

Stack *stacks;
int num_stacks;

void init_stack(int num_stacks_)
{
    num_stacks = num_stacks_;
    stacks = (Stack *)malloc(num_stacks * sizeof(Stack));
    if (stacks == NULL)
    {
        fprintf(stderr, "Memory allocation failed in init_stack()\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_stacks; i++)
    {
        stacks[i].arr = (void **)malloc(sizeof(void *));
        if (stacks[i].arr == NULL)
        {
            fprintf(stderr, "Memory allocation failed in init_stack()\n");
            exit(EXIT_FAILURE);
        }
        stacks[i].top_index = -1;
        stacks[i].size = 1;
    }
}

void push(int stack_id, void *object)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in push()\n");
        return;
    }
    printf("Pushing %d to stack %d\n", *(int *)object, stack_id);

    if (object == NULL)
        return;

    if (stacks[stack_id].top_index == stacks[stack_id].size - 1)
    {
        size_t new_size = stacks[stack_id].size * 2;
        void **new_arr = (void **)realloc(stacks[stack_id].arr, new_size * sizeof(void *));
        if (new_arr == NULL)
        {
            fprintf(stderr, "Memory allocation failed in push()\n");
            return;
        }
        stacks[stack_id].arr = new_arr;
        stacks[stack_id].size = new_size;
    }
    stacks[stack_id].top_index++;
    stacks[stack_id].arr[stacks[stack_id].top_index] = object;
}

void *pop(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in pop()\n");
        return NULL;
    }
    if (stacks[stack_id].top_index == -1)
    {
        return NULL;
    }
    void *object = stacks[stack_id].arr[stacks[stack_id].top_index];
    stacks[stack_id].top_index--;
    return object;
}

void display_int_stack(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in display_int_stack()\n");
        return;
    }
    if (stacks[stack_id].top_index == -1)
    {
        printf("Stack %d is empty\n", stack_id);
        return;
    }

    printf("Stack %d (top to bottom):\n", stack_id);
    for (int i = stacks[stack_id].top_index; i >= 0; i--)
    {
        printf("%d\n", *(int *)stacks[stack_id].arr[i]); // only works for int
    }
}

int size(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in size()\n");
        return -1;
    }
    return stacks[stack_id].top_index + 1;
}

int isEmpty(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in isEmpty()\n");
        return 1;
    }
    return stacks[stack_id].top_index == -1;
}

void *top(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID in top()\n");
        return NULL;
    }
    return stacks[stack_id].arr[stacks[stack_id].top_index];
}
