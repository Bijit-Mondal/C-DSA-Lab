// Using a stack, write a program to convert an infix expression into its equivalent postfix expression
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int precedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

int main()
{
    int num_stacks = 1;
    init_stack(num_stacks);
    char infix[100];
    char postfix[100];
    int stack_id = 0;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    printf("Infix expression: %s\n", infix);

    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++)
    {
        c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(stack_id, &c);
        }
        else if (c == ')')
        {
            while (!isEmpty(stack_id) && *((char *)top(stack_id)) != '(')
            {
                postfix[j++] = *((char *)pop(stack_id));
            }
            if (!isEmpty(stack_id) && *((char *)top(stack_id)) != '(')
            {
                printf("Invalid Expression\n");
                return 1;
            }
            else
            {
                pop(stack_id);
            }
        }
        else
        {
            while (!isEmpty(stack_id) && precedence(c) <= precedence(*((char *)top(stack_id))))
            {
                postfix[j++] = *((char *)pop(stack_id));
            }
            push(stack_id, &c);
        }
    }

    while (!isEmpty(stack_id))
    {
        postfix[j++] = *((char *)pop(stack_id));
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
