//
//  main.c
//  Homework3
//
//  Created by aprirez on 9/16/21.
//
// Alla Prirez
// Description:
//1. Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.
//2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define N 5
#define M 5

void printPaths(int n, int m, int a[N][M]) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}

void pathsWithObstacles(int planWithObstacles[N][M]) {
    int paths[N][M];
    
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++)
        {
            paths[i][j] = 0;
        }
    }
    
    if (planWithObstacles[0][0] == 0)
        paths[0][0] = 1;

    for (int i = 1; i < N; i++) {
      if (planWithObstacles[i][0] == 0)
        paths[i][0] = paths[i - 1][0];
    }

    for (int j = 1; j < M; j++) {
      if (planWithObstacles[0][j] == 0)
        paths[0][j] = paths[0][j - 1];
    }
 
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            if (planWithObstacles[i][j] == 0)
                paths[i][j] = paths[i - 1][j] +
                paths[i][j - 1];
        }
    }
    printPaths(N, M, paths);
  }

void print(char x[20], char b[20][20], int i, int j) {
    if (i == 0 || j == 0)
        return;

    if (b[i][j] == 'c') {
        print(x, b, i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
    else if (b[i][j] == 'u') {
        print(x, b, i - 1, j);
    }
    else {
        print(x, b, i, j - 1);
    }
}

void lcs(char x[20], char y[20]) {
    int i, j, m, n;

    int  c[20][20];
    char b[20][20];

    memset(c, 0, sizeof(int)  * 20 * 20);
    memset(b, 0, sizeof(char) * 20 * 20);

    m = (int) strlen(x);
    n = (int) strlen(y);
    
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'c';
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'u';
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'l';
            }
        }
    }

    print(x, b, m, n);
    printf("\n");
    
    printf("\nMatrix C\n");
    for (i = 0; i <= m; i++) {
        for(j = 0; j <= n; j++) {
            printf("%02d ", c[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMatrix B\n");
    for (i = 0; i <= m; i++) {
        for(j = 0; j <= n; j++) {
            printf("%c ", b[i][j] ? b[i][j] : '.');
        }
        printf("\n");
    }

}

int main() {
    char x[20], y[20];
    
    printf("Number of paths in matrix with obstacles\n");
    int array[N][M] = {
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 1, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 }
    };
    pathsWithObstacles(array);
    
    printf("\nLongest Common Subsequence\n");
    printf("Enter 1st sequence: ");
    // may crash if input is more than 19 symbols
    scanf("%s", x);
    
    printf("Enter 2nd sequence: ");
    // may crash if input is more than 19 symbols
    scanf("%s", y);
    
    printf("The longest common subsequence is: ");
    lcs(x, y);

    printf("\n");
    return 0;
}
