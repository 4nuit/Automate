#ifndef STACK_H
#define STACK_H

typedef struct stack stack;

/*
requires: nothing
assigns: nothing
ensures: return an empty stack 
*/
stack new_s();

/*
requires: nothnig
assigns: nothing
ensures: return (s is empty) 
*/
int isEmpty(stack s);

/*
requires: stack s not full, int e
assigns: *s
ensures: put e on the top of s 
*/
void push(stack *s, int e);

/*
requires: nothing (isEmpty call is stack is empty)
assigns: *s
ensures: return and remove the last element of s
*/
int pop(stack *s);

/*
requires: nothing (isEmpty call is stack is empty)
assigns: *s
ensures: return the last element of s
*/
int last(stack *s);

/*
requires: nothing
assigns: *s
ensures: print s without destroying it
*/
void printStack(stack *s);

#endif