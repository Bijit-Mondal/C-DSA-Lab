#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

Stack *stacks;
int num_stacks;

void init_stack(int num_stacks_)
{
    num_stacks = num_stacks_;
    stacks = (Stack *)malloc(num_stacks * sizeof(Stack));
    if (stacks == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_stacks; i++)
    {
        stacks[i].top = NULL;
    }
}

void push(int stack_id, void *object)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = object;
    newNode->next = stacks[stack_id].top;
    stacks[stack_id].top = newNode;
}

void *pop(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return NULL;
    }
    if (stacks[stack_id].top == NULL)
    {
        return NULL;
    }
    Node *temp = stacks[stack_id].top;
    void *data = temp->data;
    stacks[stack_id].top = temp->next;
    free(temp);
    return data;
}

int size(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return -1;
    }
    int count = 0;
    Node *current = stacks[stack_id].top;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

int isEmpty(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return 1;
    }
    return stacks[stack_id].top == NULL;
}

void *top(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return NULL;
    }
    if (stacks[stack_id].top == NULL)
    {
        return NULL;
    }
    return stacks[stack_id].top->data;
}

void display_int_stack(int stack_id)
{
    if (stack_id < 0 || stack_id >= num_stacks)
    {
        fprintf(stderr, "Invalid stack ID\n");
        return;
    }
    if (stacks[stack_id].top == NULL)
    {
        printf("Stack is empty\n");
        return;
    }
    Node *current = stacks[stack_id].top;
    printf("Stack (top to bottom):\n");
    while (current != NULL)
    {
        printf("%d\n", *(int *)current->data);
        current = current->next;
    }
}