// 8. Write a program to check balanced brackets of an expression using stack.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int areBracketsBalanced(char *expression)
{
    int num_stacks = 1;
    init_stack(num_stacks);
    int stack_id = 0;
    int i;
    char c;

    for (i = 0; expression[i] != '\0'; i++)
    {
        c = expression[i];
        if (c == '(' || c == '{' || c == '[')
        {
            push(stack_id, &c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (isEmpty(stack_id))
            {
                return 0;
            }
            char *top = (char *)top(stack_id);
            pop(stack_id);
            if ((c == ')' && *top != '(') || (c == '}' && *top != '{') || (c == ']' && *top != '['))
            {
                return 0;
            }
        }
    }
    return isEmpty(stack_id) ? 1 : 0;
}

int main()
{
    char expression[100];
    printf("Enter expression: ");
    scanf("%s", expression);
    if (areBracketsBalanced(expression))
    {
        printf("Brackets are balanced\n");
    }
    else
    {
        printf("Brackets are not balanced\n");
    }
    return 0;
}
