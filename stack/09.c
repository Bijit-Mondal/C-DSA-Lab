// 9. Write a program to implement queue data structure using an array.
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct
{
    int stack1_id;
    int stack2_id;
} Queue;

void enqueue(Queue *q, void *data)
{
    push(q->stack1_id, data);
}

void *dequeue(Queue *q)
{
    if (isEmpty(q->stack2_id))
    {
        while (!isEmpty(q->stack1_id))
        {
            push(q->stack2_id, pop(q->stack1_id));
        }
    }
    return pop(q->stack2_id);
}

int isEmptyQueue(Queue *q)
{
    return isEmpty(q->stack1_id) && isEmpty(q->stack2_id);
}

void *peek(Queue *q)
{
    if (isEmpty(q->stack2_id))
    {
        while (!isEmpty(q->stack1_id))
        {
            push(q->stack2_id, pop(q->stack1_id));
        }
    }
    return top(q->stack2_id);
}

void displayQueue(Queue *q)
{
    if (isEmpty(q->stack2_id))
    {
        while (!isEmpty(q->stack1_id))
        {
            push(q->stack2_id, pop(q->stack1_id));
        }
    }
    display_int_stack(q->stack2_id);
}

int main()
{
    int num_stacks = 2;
    init_stack(num_stacks);

    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->stack1_id = 0;
    q->stack2_id = 1;

    int a = 10, b = 20, c = 30;
    enqueue(q, &a);
    enqueue(q, &b);
    enqueue(q, &c);

    printf("Queue: \n");
    displayQueue(q);

    printf("Dequeue: %d\n", *(int *)dequeue(q));
    printf("Dequeue: %d\n", *(int *)dequeue(q));

    printf("Queue: \n");
    displayQueue(q);

    printf("Peek: %d\n", *(int *)peek(q));

    printf("Is empty: %s\n", isEmptyQueue(q) ? "Yes" : "No");

    return 0;
}
