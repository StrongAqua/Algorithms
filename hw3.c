//
//  main.c
//  Homework3
//
//  Created by aprirez on 9/16/21.
//
// Alla Prirez
//1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения оптимизированной и не оптимизированной программы. Написать функции сортировки, которые возвращают количество операций.
//2. *Реализовать шейкерную сортировку.
//3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив. Функция возвращает индекс найденного элемента или -1, если элемент не найден.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define MaxN 100

void fillingArray(int* array, int size) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

void swap(int* array, int j) {
    int temp = array[j - 1];
    array[j - 1] = array[j];
    array[j] = temp;
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
        printf("\n");
}

int bubbleSort(int* array, int size) {
    int iterationsCount = 0;
    for (int i = 0; i < size; i++) {
        int internalCount = 0;
        for (int j = (size - 1); j > i; j--) {
            if (array[j - 1] > array[j]) {
                swap(array, j);
            }
            iterationsCount++;
            internalCount++;
        }
    }
    return iterationsCount;
}

int bubbleSortOpt(int* array, int size) {
    int iterationsCount = 0;

    for (int i = 0; i < size; i++) {
        int swapped = 0;
        int internalCount = 0;
        for (int j = (size - 1); j > i; j--) {
            if (array[j - 1] > array[j]) {
                swap(array, j);
                swapped = 1;
            }
            iterationsCount++;
            internalCount++;
        }
        if (swapped == 0)
           break;
    }
    return iterationsCount;
}

int cocktailSort(int* array, int size) {
    int start = 0;
    int end = size - 1;
    int iterationsCount = 0;

    int swapped = 0;

    do {
        swapped = 0;
        int internalCount = 0;

        for (int i = end; i > start; i--) {
            if (array[i - 1] > array[i]) {
                swap(array, i);
                swapped = 1;
            }
            iterationsCount++;
            internalCount++;
        }

        if (swapped == 0)
            break;

        start++;
        swapped = 0;
        internalCount = 0;

        for (int i = start; i <= end; i++) {
            if (array[i - 1] > array[i]) {
                swap(array, i);
                swapped = 1;
            }
            iterationsCount++;
            internalCount++;
        }

        end--;

    } while (swapped);

    return iterationsCount;
}

int binarySearch(int *array, int left, int right, int searchNum) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (array[mid] == searchNum)
            return mid;
  
        if (array[mid] > searchNum)
            return binarySearch(array, left, mid - 1, searchNum);
  
        return binarySearch(array, mid + 1, right, searchNum);
    }
  
    return -1;
}

int main() {
    int array[MaxN];
    int tempArray[MaxN];
    int iterationCount = 0;
    
    printf("Bubble Sorter\n");
    fillingArray(array, MaxN);

    printf("Not sorted array is:\n");
    printArray(array, MaxN);
    
    printf("\nSort array using Bubble sort\n");
    memcpy(tempArray, array, MaxN * sizeof(int));
    iterationCount = bubbleSort(tempArray, MaxN);
    printf("\nSorted array is:\n");
    printArray(tempArray, MaxN);
    printf("Iterations count: %d\n", iterationCount);
    
    printf("\nAn optimized version of Bubble Sort\n");
    memcpy(tempArray, array, MaxN * sizeof(int));
    iterationCount = bubbleSortOpt(tempArray, MaxN);
    printf("Sorted array is:\n");
    printArray(tempArray, MaxN);
    printf("Iterations count: %d\n", iterationCount);
    
    printf("\nSort array using Cocktail sort\n");
    memcpy(tempArray, array, MaxN * sizeof(int));
    iterationCount = cocktailSort(tempArray, MaxN);
    printf("Sorted array is:\n");
    printArray(tempArray, MaxN);
    printf("Iterations count: %d\n", iterationCount);
    
    int searchNum = 0;
    printf("\nInput value for search: ");
    scanf("%i", &searchNum);
    int result = binarySearch(tempArray, 0, MaxN, searchNum);
    (result == -1) ? printf("Element is not present in array\n")
                   : printf("Element is present at index %d\n", result);

    return 0;
}
