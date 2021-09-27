//
//  main.c
//  Homework6
//
//  Created by aprirez on 9/27/21.
//
// Alla Prirez
// Description:
//1. Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
//2. Переписать программу, реализующую двоичное дерево поиска.
//а) Добавить в него обход дерева различными способами;
//б) Реализовать поиск в двоичном дереве поиска;

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef int bool;

// ------------------------------------------------
// task 1
int sumHash(char str[100]) {
    int i = 0, sum = 0;
    while (str[i] != '\0') {
        printf("\nThe ascii value of the character %c is %d", str[i], str[i]);
        sum = sum + str[i];
        i++;
    }
    printf("\nSum of the ascii value of a string: %d\n", sum);
    return sum;
}

void solution1() {
    char str[100] = "";
    printf("Implement the simplest hash function\n");
    printf("Enter a string: ");
    do {
        fgets(str, sizeof(str), stdin);
    } while (!strlen(str) || str[0] == '\n');
    str[strlen(str) - 1] = 0;
    printf("Result of hash function is: %d\n", sumHash(str));
}

// ------------------------------------------------
// task 2
typedef struct _Node {
    int data;
    struct _Node* left;
    struct _Node* right;
    struct _Node* parent;
} Node;
 
Node* newNode(int data, Node* parent) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
 
    return node;
}

Node* insert(Node* node, int data) {
    if (node == NULL)
        return newNode(data, NULL);

    if (data < node -> data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
 
    return node;
}

void printTree(Node *node) {
    if (node) {
        printf("%d", node->data);
        if (node->left || node->right) {
            printf("(");
            if (node->left)
                printTree(node->left);
            else
                printf("NULL");
            printf(",");
            if (node->right)
                printTree(node->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

bool search(Node* node, int data) {
    
    while (node != NULL) {
        if (data > node->data)
            node = node->right;
        else if (data < node->data)
            node = node->left;
        else
            return 1;
    }
    return 0;
}
 
void printPostOrder(Node* node) {
    if (node == NULL)
        return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->data);
}

void printInOrder(Node* node) {
    if (node == NULL)
        return;
    printInOrder(node->left);
    printf("%d ", node->data);
    printInOrder(node->right);
}
 
void printPreOrder(Node* node) {
    if (node == NULL)
        return;
    printf("%d ", node->data);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

void solution2() {
    printf("Rewrite a program that implements search in a binary tree\n");
    Node* root = NULL;
    int searchValue = 22;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    printf("Your tree is: ");
    printTree(root);
    printf("\n");
    if (search(root, searchValue))
        printf("The value '%d' exists in the tree\n", searchValue);
    else
        printf("The value '%d' doesn't exist in the tree\n", searchValue);
    
    printf("Pre-order trace of binary tree is \n");
    printPreOrder(root);
    
    printf("\nIn-order trace of binary tree is \n");
    printInOrder(root);
    
    printf("\nPost-order trace of binary tree is \n");
    printPostOrder(root);
}

// ------------------------------------------------
// Main
int main() {
    int taskNumber = 0;

    do {
        printf("\n");
        printf("Select number of task:\n");
        printf("1 - Implement the simplest hash function\n");
        printf("2 - Rewrite a program that implements a binary search tree\n");
        printf("0 - For exit\n");
        printf("Your choice: ");
        scanf("%i", &taskNumber);
        switch (taskNumber) {
            case 1:
                solution1();
                break;
            case 2:
                solution2();
                break;
            case 0:
                printf("Good luck!\n");
                break;
            default:
                printf("Wrong selection\n");
        }
    } while (taskNumber != 0);
    return 0;
}
