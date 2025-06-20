#include <stdio.h>
#include "stack.h"

int main()
{
    int num_stacks = 3;
    init_stack(num_stacks);

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    push(0, &a);
    push(0, &b);
    push(1, &c);
    push(1, &d);
    push(2, &e);

    printf("Stack 0:\n");
    display_int_stack(0);
    printf("Stack 1:\n");
    display_int_stack(1);
    printf("Stack 2:\n");
    display_int_stack(2);

    printf("Pop from stack 0: %d\n", *(int *)pop(0));
    printf("Pop from stack 1: %d\n", *(int *)pop(1));
    printf("Pop from stack 2: %d\n", *(int *)pop(2));

    printf("Stack 0 size: %d\n", size(0));
    printf("Stack 1 size: %d\n", size(1));
    printf("Stack 2 size: %d\n", size(2));

    return 0;
}
