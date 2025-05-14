#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int stack[SIZE];
int top = 0;

void push(int value);
int pop();
int empty();
int stackpop();

int main()
{
    if(empty()){
        printf("Vazio");
    }
    push(10);
    push(9);
    push(8);
    push(7);
    push(6);
    push(5);
    push(4);
    push(3);
    push(2);
    push(1);
    printf("Get out: %d\n", pop());
    printf("Get out: %d\n", pop());

    return 0;
}

void push(int value)
{
    if (top >= SIZE)
    {
        printf("Stack is full");
    }
    else
    {
        stack[top++] = value;
    }
}

int pop()
{
    if (top == 0)
    {
        printf("Empty Stack");
    }
    else
    {
        return stack[--top];
    }
}

int stackpop()
{
    if (top == 0)
    {
        printf("Empty List");
    }
    else
    {
        return stack[top - 1];
    }
}

int empty()
{
    return top == 1 ? 1 : 0;
}