#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{

    struct Node *top;

} Stack;

typedef struct Node
{

    int value;
    struct Node *next;

} Node;

void push(Stack *stack, int value);
Node *makeNode();
Stack *makeStack();
int empty(Stack *stack);
int pop(Stack *stack);

int main()
{
    Stack *firstStack = makeStack();
    push(firstStack, 10);
    push(firstStack, 20);
    push(firstStack, 30);
    push(firstStack, 40);

    while (!empty(firstStack))
    {
        printf("Getting out the stack: %d\n", firstStack->top->value);
        pop(firstStack);
    }

    return 0;
}

void push(Stack *stack, int value)
{

    Node *newNode = makeNode();

    newNode->value = value;

    if (empty(stack))
    {
        printf("\nEmpty Stack\n\n");
        printf("Adding value: %d\n", value);
        stack->top = newNode;
    }
    else
    {
        printf("Adding value: %d\n", value);
        newNode->next = stack->top;
        stack->top = newNode;
    }
}

Node *makeNode()
{
    return (Node *)calloc(1, sizeof(Node));
}

Stack *makeStack()
{
    return (Stack *)calloc(1, sizeof(Stack));
}

int empty(Stack *stack)
{
    if (stack->top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pop(Stack *stack)
{
    int back;

    if (empty(stack))
    {
        return 0;
    }
    else
    {
        back = stack->top->value;
        stack->top = stack->top->next;
        return back;
    }
}