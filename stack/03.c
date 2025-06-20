#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    int stack_id = 0;
    int num_stacks = 1;
    init_stack(num_stacks);

    FILE *fp;
    int num;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    while (fscanf(fp, "%d", &num) == 1)
    {
        int *data = (int *)malloc(sizeof(int));
        if (data == NULL)
        {
            perror("Memory allocation failed");
            fclose(fp);
            return 1;
        }
        *data = num;
        push(stack_id, data);
    }

    fclose(fp);

    printf("Reversed order:\n");
    while (!isEmpty(stack_id))
    {
        int *data = (int *)pop(stack_id);
        printf("%d\n", *data);
        free(data);
    }

    return 0;
}
