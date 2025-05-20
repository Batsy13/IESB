#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{

    int value;
    struct Node *next;
    struct Node *prev;

} Node;

typedef struct List
{

    int qtd;
    struct Node *initial;
    struct Node *end;

} List;

Node *makeNode();
List *makeList();
void insertBeggining(List *list, int value);
void showList(List *list);
void insertFinal(List* list, int value);
void removeElement(List* list, int value);

int main()
{

    List *firstList = makeList();

    insertBeggining(firstList, 10);
    insertBeggining(firstList, 20);
    insertBeggining(firstList, 30);
    insertFinal(firstList, 5);
    showList(firstList);
    removeElement(firstList, 20);
    printf("After removing 20:\n");
    showList(firstList);

    return 0;
}

Node *makeNode()
{
    return (Node *)calloc(1, sizeof(Node));
}

List *makeList()
{
    return (List *)calloc(1, sizeof(List));
}

void insertBeggining(List *list, int value)
{

    Node *newNode = makeNode();
    newNode->value = value;

    if (list->initial == NULL)
    {
        printf("Empty List\n");
        list->initial = newNode;
        list->end = newNode;
    }
    else
    {
        list->initial->prev = newNode;
        newNode->next = list->initial;
        list->initial = newNode;
    }
}

void insertFinal(List* list, int value){
    Node *newNode = makeNode();
    newNode->value = value;

    if (list->end == NULL) {
        list->initial = newNode;
        list->end = newNode;
    } else {
        list->end->next = newNode;
        newNode->prev = list->end;
        list->end = newNode;
    }
}

void removeElement(List* list, int value) {
    if (list->initial == NULL) {
        return;
    }
    Node *current = list->initial;
    while (current != NULL) {
        if (current->value == value) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                list->initial = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                list->end = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

void showList(List *list)
{

    Node *aux = makeNode();

    if (list->initial == NULL)
    {
        printf("Empty List\n");
    }
    else
    {

        aux = list->initial;

        while (aux != NULL)
        {
            printf("Value: %d\n", aux->value);

            aux = aux->next;
        }
    }
}