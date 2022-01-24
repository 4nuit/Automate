#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define N 256 

struct stack { /*pile = un top et un pointeur vers l'élément suivant*/
    int stack[N];
    int top;
};

typedef struct stack stack;

/*Création d'une pile*/
stack new_s() { 
    stack s;
    s.top = -1;
    return s;
}

int isEmpty(stack s) {
    return (s.top < 0);
}

/*Empile*/
void push(stack *s, int e) {
    if (s->top == N-1) {
        printf("Stack is full"); 
    }
    s->top += 1;
    s->stack[s->top] = e;
}

/*Dépile*/
int pop(stack *s) {
    if (isEmpty(*s)) {
        printf("Stack is empty, cannot pop last element");
        return 0;
    }
    int e = s->stack[s->top];
    s->top -= 1;
    return e;
}

/*Renvoie le dernier élément*/
int last(stack *s) {
    if (isEmpty(*s)) {
        printf("Stack is empty, cannot pop last element");
        return 0;
    }
    return s->stack[s->top];
}


/*Affichage test*/
void printStack(stack *s) {
    stack t = *s;  /*t = copie de s*/
    printf("----\n");
    /*affiche puis retire les éléments de s*/
    while (!isEmpty(t)) {
        printf("%d\n", pop(&t));
    }
    printf("----\n");
}