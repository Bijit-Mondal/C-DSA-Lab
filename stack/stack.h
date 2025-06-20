#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void init_stack(int num_stacks);

    void push(int stack_id, void *object);

    void *pop(int stack_id);

    int size(int stack_id);

    int isEmpty(int stack_id);

    void *top(int stack_id);

    void display_int_stack(int stack_id);

#ifdef __cplusplus
}
#endif