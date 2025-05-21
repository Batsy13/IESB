#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree
{
    struct Node *root;
} Tree;

Node *makeNode();
Tree *makeTree();
void insert(Tree *tree, int value);
void insertNode(Node *root, Node *newNode);
void printTreeInOrder(Node *node);

int main()
{
    Tree *firstTree = makeTree();
    insert(firstTree, 18);
    insert(firstTree, 10);
    insert(firstTree, 3);
    insert(firstTree, 120);
    insert(firstTree, 5);
    insert(firstTree, 1);
    insert(firstTree, 20);

    printf("Tree in crescent order:\n");
    printTreeInOrder(firstTree->root);
    printf("\n");

    return 0;
}

Node *makeNode()
{
    return (Node *)calloc(1, sizeof(Node));
}

Tree *makeTree()
{
    Tree *newTree = (Tree *)calloc(1, sizeof(Tree));
    newTree->root = NULL;
    return newTree;
}

void insert(Tree *tree, int value)
{
    Node *newNode = makeNode();
    newNode->value = value;

    if (tree->root == NULL)
    {
        tree->root = newNode;
        return;
    }
    insertNode(tree->root, newNode);
}

void insertNode(Node *root, Node *newNode)
{
    if (newNode->value < root->value)
    {
        if (root->left == NULL)
        {
            root->left = newNode;
        }
        else
        {
            insertNode(root->left, newNode);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = newNode;
        }
        else
        {
            insertNode(root->right, newNode);
        }
    }
}

void printTreeInOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    printTreeInOrder(node->left);
    printf("%d ", node->value);
    printTreeInOrder(node->right);
}