#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{

    struct Node *first;
    struct Node *last;

} Queue;

typedef struct Node
{

    int value;
    struct Node *next;

} Node;

Node *makeNode();
Queue *makeQueue();
void add(Queue *Queue, int value);
void showQueue(Queue *Queue);
void removeFromQueue(Queue *Queue);
int isEmpty(Queue *Queue);
void peek(Queue *Queue);

int main()
{

    Queue *firstQueue = makeQueue();

    add(firstQueue, 1);
    add(firstQueue, 2);
    add(firstQueue, 3);
    add(firstQueue, 4);
    add(firstQueue, 5);
    showQueue(firstQueue);

    printf("\n");

    removeFromQueue(firstQueue);
    removeFromQueue(firstQueue);

    printf("\n");

    showQueue(firstQueue);

    printf("\n");

    peek(firstQueue);

    return 0;
}

void add(Queue *Queue, int value)
{

    Node *newNode = makeNode();
    newNode->value = value;

    if (isEmpty(Queue))
    {
        Queue->first = newNode;
        Queue->last = newNode;
    }
    else
    {
        Queue->last->next = newNode;
        Queue->last = newNode;
    }
}

void showQueue(Queue *Queue)
{

    if (isEmpty(Queue))
    {
        printf("Empty Queue\n");
    }
    else
    {

        Node *aux = makeNode();

        aux = Queue->first;
        int i;
        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                printf("Queue's end: %d\n", aux->value);
            }
            else
            {
                printf("Value: %d\n", aux->value);
            }
            aux = aux->next;
        }
    }
}

void removeFromQueue(Queue *Queue)
{

    if (isEmpty(Queue))
    {
        printf("Empty Queue\n");
    }
    else
    {
        Node *aux = makeNode();
        aux = Queue->first->next;
        printf("Leaving the Queue: %d\n", Queue->first->value);
        free(Queue->first);
        Queue->first = aux;
    }
}

int isEmpty(Queue *Queue)
{

    return Queue->first == NULL ? 1 : 0;
}

void peek(Queue *Queue)
{
    printf("Peek: %d", Queue->first->value);
}

Node *makeNode()
{
    return (Node *)calloc(1, sizeof(Node));
}

Queue *makeQueue()
{
    return (Queue *)calloc(1, sizeof(Queue));
}