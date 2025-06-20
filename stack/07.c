// 7. Write a program to evaluate postfix expression using a stack.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int evaluatePostfix(char *postfix)
{
    int num_stacks = 1;
    init_stack(num_stacks);
    int stack_id = 0;
    int i;
    char c;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        c = postfix[i];
        if (isdigit(c))
        {
            push(stack_id, (void *)(c - '0'));
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            int operand2 = (int)pop(stack_id);
            int operand1 = (int)pop(stack_id);
            int result;
            switch (c)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            }
            push(stack_id, (void *)result);
        }
    }
    return (int)pop(stack_id);
}

int main()
{
    char postfix[100];
    printf("Enter postfix expression: ");
    scanf("%s", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}
