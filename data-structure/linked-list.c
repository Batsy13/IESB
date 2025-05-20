#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    struct Node *init;
    int qtd;
} List;

typedef struct Node
{
    int value;
    struct Node *next;

} Node;

Node *makeNode();
List *makeList();
void showList(List *list);
void addNodeInit(List *list, int value);
void addNodeFinal(List* list, int value);

int main()
{
    List *FirstList = makeList();
    addNodeInit(FirstList, 40);
    addNodeInit(FirstList, 30);
    addNodeInit(FirstList, 20);
    showList(FirstList);
    printf("-----------------------\n");
    addNodeFinal(FirstList, 50);
    showList(FirstList);
}

Node *makeNode()
{
    return (Node *)calloc(1, sizeof(Node));
}

List *makeList()
{
    return (List *)calloc(1, sizeof(List));
}

void showList(List *list)
{
    if (list->init == NULL)
    {
        printf("Empty List\n");
    }
    else
    {
        Node *aux = makeNode();

        aux = list->init;

        while (aux != NULL)
        {
            printf("%d\n", aux->value);
            aux = aux->next;
        }
    }
}

void addNodeInit(List *list, int value)
{
    Node *newNode = makeNode();
    newNode->value = value;

    if (list->init == NULL)
    {
        list->init = newNode;
    }
    else
    {
        newNode->next = list->init;
        list->init = newNode;
    }
    list->qtd++;
}

void addNodeFinal(List *list, int value)
{
    Node *newNode = makeNode();
    newNode->value = value;

    Node *aux = makeNode();

    if (list->init == NULL)
    {
        list->init = newNode;
    }
    else
    {
        aux = list->init;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = newNode;
    }
    list->qtd++;
}