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

void display(){
    Poly *p = start;
    if(p == NULL){
        printf("Polynomial is empty\n");
        return;
    }

    while(p != NULL){
        printf("%dX^%d", p->coeff, p->exp);
        p = p->link;
        if(p != NULL){
            printf(" + ");
        }
    }
    printf("\n");
}

Poly* add(Poly *start1, Poly *start2){
    Poly *result = NULL;
    Poly *last = NULL;
    Poly *p1 = start1;
    Poly *p2 = start2;

    while(p1 != NULL && p2 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return result;
        }

        if(p1->exp > p2->exp){
            new->coeff = p1->coeff;
            new->exp = p1->exp;
            p1 = p1->link;
        } else if(p1->exp < p2->exp){
            new->coeff = p2->coeff;
            new->exp = p2->exp;
            p2 = p2->link;
        } else { // Equal exponents
            new->coeff = p1->coeff + p2->coeff;
            new->exp = p1->exp;
            p1 = p1->link;
            p2 = p2->link;
        }

        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
    }

    // Add remaining terms from p1
    while(p1 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return result;
        }
        new->coeff = p1->coeff;
        new->exp = p1->exp;
        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
        p1 = p1->link;
    }

    // Add remaining terms from p2
    while(p2 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return result;
        }
        new->coeff = p2->coeff;
        new->exp = p2->exp;
        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
        p2 = p2->link;
    }

    return result;
}

void insert(int pos, int coeff, int exp){
    if(pos < 1) return;
    Poly *new = createnode();
    if(new == NULL){
        printf("\nMemory allocation failed!");
        return;
    }
    new->coeff = coeff;
    new->exp = exp;
    new->link = NULL;

    if(pos == 1){
        new->link = start;
        start = new;
        return;
    }

    Poly *pre = start;
    int idx = 1;
    while(pre != NULL && idx < pos - 1){
        pre = pre->link;
        idx++;
    }

    if(pre == NULL){
        printf("\nInvalid position %d for insertion.", pos);
        free(new);
        return;
    }
    new->link = pre->link;
    pre->link = new;
}

void freeList(Poly *head){
    Poly *temp;
    while(head != NULL){
        temp = head;
        head = head->link;
        free(temp);
    }
}

void multiPly(Poly *start1, Poly *start2) {
    Poly *result = NULL;
    Poly *last = NULL;
    for(Poly *p1 = start1; p1 != NULL; p1 = p1->link) {
        for(Poly *p2 = start2; p2 != NULL; p2 = p2->link) {
            int newCoeff = p1->coeff * p2->coeff;
            int newExp = p1->exp + p2->exp;

            Poly *temp = result;
            int found = 0;

            while(temp != NULL) {
                if(temp->exp == newExp) {
                    temp->coeff += newCoeff;
                    found = 1;
                    break;
                }
                temp = temp->link;
            }

            if(!found) {
                Poly *new = createnode();
                if(new == NULL){
                    printf("\nMemory allocation failed!");
                    return;
                }
                new->coeff = newCoeff;
                new->exp = newExp;
                new->link = NULL;

                if(result == NULL) {
                    result = new;
                    last = new;
                }else{
                    last->link = new;
                    last = new;
                }
            }
        }
    }
    start = result;
}

void subtract(Poly *start1,Poly *start2){
    Poly *result = NULL;
    Poly *last = NULL;
    Poly *p1 = start1;
    Poly *p2 = start2;

    while(p1 != NULL && p2 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return;
        }

        if(p1->exp > p2->exp){
            new->coeff = p1->coeff;
            new->exp = p1->exp;
            p1 = p1->link;
        } else if(p1->exp < p2->exp){
            new->coeff = -p2->coeff;
            new->exp = p2->exp;
            p2 = p2->link;
        } else {
            new->coeff = p1->coeff - p2->coeff;
            new->exp = p1->exp;
            p1 = p1->link;
            p2 = p2->link;
        }

        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
    }

    while(p1 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return;
        }
        new->coeff = p1->coeff;
        new->exp = p1->exp;
        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
        p1 = p1->link;
    }
    while(p2 != NULL){
        Poly *new = createnode();
        if(new == NULL){
            printf("\nMemory allocation failed!");
            return;
        }
        new->coeff = -p2->coeff;
        new->exp = p2->exp;
        new->link = NULL;

        if(result == NULL){
            result = new;
            last = new;
        } else {
            last->link = new;
            last = new;
        }
        p2 = p2->link;
    }

    start=result;
}

int main(){
    printf("\n1. Insert\n2. Display\n3. Exit\n4. Add\n5. Multiply\n6. Subtract\n");
    int choice;
    while(1){
        printf("\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                int pos, coeff, exp;
                printf("Enter position, coefficient and exponent: ");
                scanf("%d %d %d", &pos, &coeff, &exp);
                insert(pos, coeff, exp);
                break;
            case 2:
                display();
                break;
            case 3:
                exit(0);
                break;
            case 4:
                {
                    freeList(start);
                    Poly *start1 = NULL;
                    Poly *start2 = NULL;
                    int n1, n2, coeff, exp;

                    printf("Enter number of terms in first polynomial: ");
                    scanf("%d", &n1);
                    for(int i = 0; i < n1; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start1 = start;

                    start = NULL;
                    printf("Enter number of terms in second polynomial: ");
                    scanf("%d", &n2);
                    for(int i = 0; i < n2; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start2 = start;

                    Poly *result = add(start1, start2);
                    start = result;
                    printf("Resultant Polynomial: ");
                    display();

                    freeList(start1);
                    freeList(start2);
                }
                break;
            case 5:
                {
                    freeList(start);
                    Poly *start1 = NULL;
                    Poly *start2 = NULL;
                    int n1, n2, coeff, exp;

                    printf("Enter number of terms in first polynomial: ");
                    scanf("%d", &n1);
                    for(int i = 0; i < n1; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start1 = start;

                    start = NULL;
                    printf("Enter number of terms in second polynomial: ");
                    scanf("%d", &n2);
                    for(int i = 0; i < n2; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start2 = start;

                    multiPly(start1, start2);
                    printf("Resultant Polynomial after multiplication: ");
                    display();

                    freeList(start1);
                    freeList(start2);
                }
                break;
            case 6:
                {
                    freeList(start);
                    Poly *start1 = NULL;
                    Poly *start2 = NULL;
                    int n1, n2, coeff, exp;

                    printf("Enter number of terms in first polynomial: ");
                    scanf("%d", &n1);
                    for(int i = 0; i < n1; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start1 = start;

                    start = NULL;
                    printf("Enter number of terms in second polynomial: ");
                    scanf("%d", &n2);
                    for(int i = 0; i < n2; i++){
                        printf("Enter coefficient and exponent: ");
                        scanf("%d %d", &coeff, &exp);
                        insert(i + 1, coeff, exp);
                    }
                    start2 = start;

                    subtract(start1,start2);

                    printf("Resultant Polynomial after multiplication: ");
                    display();

                    freeList(start1);
                    freeList(start2);

                }
            default:
                printf("\nInvalid choice. Please try again.");
        }
    }
    return 0;
}
