// Write a menu-driven program representing a polynomial as a data structure
// using a singly linked list and write functions to add, subtract and multiply
// two polynomials

#include<stdio.h>
#include<stdlib.h>

typedef struct poly{
    int coeff;
    int exp;
    struct poly *link;
}Poly;

Poly *start = NULL;

Poly *createnode(){
    Poly *t;
    t = (Poly *)malloc(sizeof(Poly));
    return(t);
}
