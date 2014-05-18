#ifndef STACK_H
#define STACK_H

#define MAXSIZE 100
typedef char datatype;
typedef struct{
   datatype a[MAXSIZE];
   int top;
 }sequence_stack;
void init(sequence_stack *st);
int empty(sequence_stack st);
datatype read(sequence_stack st);
void push(sequence_stack *st,datatype x);
void pop(sequence_stack *st);

#endif
