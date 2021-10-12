//
//  main.c
//  Homework7
//
//  Created by aprirez on 9/27/21.
//
// Alla Prirez
// Description:
//1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
//2. Написать рекурсивную функцию обхода графа в глубину.
//3. Написать функцию обхода графа в ширину.
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define Max 20
#define infinity 9999

// ------------------------------------------------
// task 1
const char* filename = "/Users/aprirez/Alla/C/Homework3/martix.txt";
int G[Max][Max], size = 5;
void printMatrix(int G[Max][Max]);

void solution1() {
    printf("Write function to read an adjacency matrix from a file and display it.\n");
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open file\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
        fscanf(file, "%d", &G[i][j]);
    }
    fclose(file);
    
    printf("Graph matrix:\n");
    printMatrix(G);
}

void printMatrix(int G[Max][Max]) {
    printf("%s", "        ");
    for (int i = 0; i < size; i++) {
        printf("%c(%d) ", 65 + i, i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%c(%d)", 65 + i, i + 1);
        for ( int j = 0; j < size; j++)
        printf("%5d", (G[i][j] == infinity) ? 0 : G[i][j]);
        printf("\n");
    }
}

// ------------------------------------------------
// task 2
int visited[20], source;

void DFS(int i) {
    int j;
    visited[i] = 1;
    printf(" %d -> ",i + 1);
    for(j = 0; j < size; j++)
    {
        if (G[i][j] != 0 && visited[j] == 0)
            DFS(j);
    }
}


void solution2() {
    printf("Write a recursive function to trace the graph in depth.\n");
    printf("Enter the source: ");
    scanf("%d",&source);
    memset(visited, 0, sizeof(visited));
    DFS(source - 1);
}

// ------------------------------------------------
// task 3
void setVisited(int n) {
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            visited[i] = n;
            break;
        }
    }
}

int isVisited(int n) {
    for (int i = 0; i < size; i++) {
        if (visited[i] == n) {
            return 1;
        }
    }
    return 0;
}

void BFS(int i) {
    int j, r = 0, item = 0;

    int queue[20];
    memset(queue, 0, sizeof(queue));

    setVisited(i);
    for (j = 1; j <= size; j++) {
        if (G[i - 1][j - 1] != 0 && isVisited(j) == 0) {
            queue[r++] = j;
        }
    }
    
    for (item = 0; item < r; item++) {
        BFS(queue[item]);
    }
}


void solution3() {
    printf("Write a function for trace the graph in width.\n");
    printf("Enter the source: ");
    scanf("%d",&source);
    memset(visited, 0, sizeof(visited));
    BFS(source);
    printf("The nodes is visited:\n");
    for (int i = 0; i < size; i++) {
        if(visited[i] == 0)
            break;
        printf("%d ", visited[i]);
    }
}

// ------------------------------------------------
// Main
int main() {
    
    int taskNumber = 0;

    do {
        printf("\n");
        printf("Select number of task:\n");
        printf("1 - Write function to read an adjacency matrix from a file and display it.\n");
        printf("2 - Write a recursive function to trace the graph in depth.\n");
        printf("3 - Write a function for trace the graph in width.\n");
        printf("0 - For exit\n");
        printf("Your choice: ");
        scanf("%i", &taskNumber);
        switch (taskNumber) {
            case 1:
                solution1();
                break;
            case 2:
                solution1();
                solution2();
                break;
            case 3:
                solution1();
                solution3();
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
