//
//  main.c
//  Homework5
//
//  Created by aprirez on 9/16/21.
//
// Alla Prirez
// Description:
//1. Реализовать перевод из десятичной в двоичную систему счисления с использованием стека.
//2. Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти. Если память не выделяется, то выводится соответствующее сообщение.
//3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef int bool;

// ------------------------------------------------
// Convert decimal to binary using stack -- helpers
#define MaxN 100

int stack[MaxN]; // arr
int stackCounter = -1;

void arr_push(int i) {
    if (stackCounter < MaxN) {
        stackCounter++;
        stack[stackCounter] = i;
    }
    else {
        printf("Stack overflow\n");
    }
}

int arr_pop() {
    if (stackCounter >= 0) {
        return stack[stackCounter--];
    }
    else {
        printf("Stack is empty\n");
        return 0;
    }
}

// ------------------------------------------------
// Program to Implement a Stack using Linked List -- helpers
typedef struct _Node {
    char value;
    struct _Node *next;
} Node;

typedef struct _Stack {
    Node *head;
    int size;
    int maxSize;
} Stack;

Stack simpleStack; // ss

void ss_stackPush(char value) {
    if (simpleStack.size >= simpleStack.maxSize) {
        printf("Error stack size\n");
        return;
    }

    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp != NULL) {
        printf("Memory allocated!\n");
        tmp->value = value;
        tmp->next = simpleStack.head;
        simpleStack.head = tmp;
        simpleStack.size++;
    } else {
        printf("Error: can't allocate memory\n");
    }
}

char ss_stackPop() {
    if (simpleStack.size == 0) {
        printf("Stack is empty\n");
        return 0;
    }
    char value = simpleStack.head->value;
    Node* next = simpleStack.head;
    simpleStack.head = simpleStack.head->next;
    free(next);
    simpleStack.size--;
    return value;
}

void ss_stackPrint()
{
    Node *current = simpleStack.head;
    while (current != NULL)
    {
        printf("%c ", current->value);
        current = current->next;
    }
}

// ------------------------------------------------
// Check the mathematical expression is correctly parenthesized -- helpers
void node_pushSub(Node** top, int value) {
    Node* new = (Node*) malloc(sizeof(Node));
    if (new == NULL) {
        printf("Error: can't allocate memory\n");
        exit(0);
    }
    new->value = value;
    new->next = (*top);
    (*top) = new;
}

int node_popSub(Node** top) {
    char res;
    Node* tmp;
    if (*top == NULL) {
        printf("Error!\n");
        exit(0);
    }
    else {
        tmp = *top;
        res = tmp->value;
        *top = tmp->next;
        free(tmp);
        return res;
    }
}

// ------------------------------------------------
// task 1
void solution1() {
    int num, total = 0;

    printf("Convert decimal to binary using stack\n");
    printf("Enter a decimal: ");
    scanf("%d", &num);
    
    while (num > 0) {
        total = num % 2;
        arr_push(total);
        num >>= 1;
    }

    while (stackCounter != -1) {
        printf("%d", arr_pop());
    }
    printf("\n");
}

// ------------------------------------------------
// task 2
void solution2() {
    printf("Program to Implement a Stack using Linked List\n");
    simpleStack.maxSize = 100;
    simpleStack.head = NULL;
    ss_stackPush('a');
    ss_stackPush('b');
    ss_stackPush('c');
    ss_stackPush('d');
    ss_stackPush('e');
    ss_stackPush('f');
    ss_stackPop();
    ss_stackPop();
    ss_stackPrint();
    printf("\n");
}

// ------------------------------------------------
// task 3
bool matchPair(char char1, char char2)
{
    if (char1 == '(' && char2 == ')')
        return 1;
    else if (char1 == '{' && char2 == '}')
        return 1;
    else if (char1 == '[' && char2 == ']')
        return 1;
    else
        return 0;
}

bool isBalanced(char sub[])
{
    int i = 0;
    Node* stackSub = NULL;

    while (sub[i]) {

        if (sub[i] == '{' || sub[i] == '(' || sub[i] == '[')
            node_pushSub(&stackSub, sub[i]);

        if (sub[i] == '}' || sub[i] == ')' || sub[i] == ']') {
            if (stackSub == NULL)
                return 0;
            else if (!matchPair(node_popSub(&stackSub), sub[i]))
                return 0;
        }

        i++;
    }
    if (stackSub == NULL)
        return 1;
    else
        return 0;
}

void solution3() {
    printf("Check the mathematical expression is correctly parenthesized\n");
    char sub[100] = "{()}[]()";
    
    if (isBalanced(sub)) {
        printf("Parenthesis sequence is balanced\n");
    }
    else {
        printf("Parenthesis sequence isn't balanced\n");
    }
    printf("\n");
}

// ------------------------------------------------
// Main
int main() {
    int taskNumber = 0;

    do {
        printf("\n");
        printf("Select number of task:\n");
        printf("1 - Convert decimal to binary using stack\n");
        printf("2 - Program to Implement a Stack using Linked List\n");
        printf("3 - Check the mathematical expression is correctly parenthesized\n");
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
            case 3:
                solution3();
                break;
            case 0:
                printf("Good luck!\n");
                break;
            default:
                printf("Wrong selected\n");
        }
    } while (taskNumber != 0);
    return 0;
}
