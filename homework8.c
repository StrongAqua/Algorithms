//
//  main.c
//  Homework8
//
//  Created by aprirez on 10/5/21.
//
// Alla Prirez
// Description:
//1. Реализовать сортировку подсчетом.
//2. Реализовать быструю сортировку.
//3. *Реализовать сортировку слиянием.
//4. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов.
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

#define Max 1000

int* array;

void fillingArray(int* array, int size) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}
// ------------------------------------------------
// task 1
void printArray(int array[], int length) {
  for (int i = 0; i < length; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

void countingSort(int array[], int length) {
    int output[length], maxNum = 0, count[Max] = {0};
    
    for (int i = 0; i < length; i++) {
        if (maxNum < array[i])
            maxNum = array[i];
    }
    
    for (int i = 0; i < length; i++) {
        count[array[i]]++;
    }
    
    for (int i = 1; i <= maxNum; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = 0; i < length; i++) {
        int indexCountArray = array[i];
        int calc = count[indexCountArray];
        output[calc - 1] = array[i];
        count[array[i]]--;
    }
            
    for (int i = 0; i < length; i++) {
        array[i] = output[i];
    }
}


void solution1(int* array, int maxLength) {
    clock_t ti;
    int* array1 = malloc(sizeof(int) * maxLength);
    memcpy (array1, array, sizeof(int)* maxLength);
    printf("Counting sort.\n");
       
    //printf("Unsorted array is: \n");
    //printArray(array1, maxLength);
    
    //printf("Sorted array is: \n");
    ti = clock();
    countingSort(array1, maxLength);
    ti = clock() - ti;
    //printArray(array1, maxLength);
    double time_taken = ((double)ti)/CLOCKS_PER_SEC;
    printf("Time complexity of Counting sort %f\n", time_taken);
    free(array1);
}
// ------------------------------------------------
// task 2
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void solution2(int* array, int maxLength) {
    clock_t ti;
    int* array2 = malloc(sizeof(int) * maxLength);
    memcpy (array2, array, sizeof(int) * maxLength);
    printf("Quick sort.\n");
    
    //printf("Unsorted array is: \n");
    //printArray(array2, maxLength);
    
    //printf("The sorted array is: \n");
    ti = clock();
    quickSort(array2, 0, maxLength - 1);
    ti = clock() - ti;
    //printArray(array2, maxLength);
    double time_taken = ((double)ti)/CLOCKS_PER_SEC;
    printf("Time complexity of Quick sort %f\n", time_taken);
    free(array2);
}

// ------------------------------------------------
// task 3
void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int L[n1], M[n2];
    
    for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];
    
    int i, j, k;
    i = 0;
    j = 0;
    k = p;
    
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        merge(arr, l, m, r);
    }
}


void solution3(int* array, int maxLength) {
    clock_t ti;
    int* array3 = malloc(sizeof(int) * maxLength);
    memcpy (array3, array, sizeof(int) * maxLength);
    printf("Merge Sort .\n");

    //printf("Unsorted array is: \n");
    //printArray(array3, maxLength);
    
    //printf("The sorted array is: \n");
    ti = clock();
    mergeSort(array3, 0, maxLength - 1);
    ti = clock() - ti;
    //printArray(array3, maxLength);
    double time_taken = ((double)ti)/CLOCKS_PER_SEC;
    printf("Time complexity of Merge sort %f\n", time_taken);
    free(array3);
}

// ------------------------------------------------
// Main
int main() {

    int taskNumber = 0;
    int max = 10;
    array = malloc(sizeof(int) * max);
    fillingArray(array, max);
    
    do {
        printf("\n");
        printf("Select number of task:\n");
        printf("1 - Write counting sort.\n");
        printf("2 - Write quick sort.\n");
        printf("3 - Write merge sort.\n");
        printf("4 - Time complexity.\n");
        printf("0 - For exit\n");
        printf("Your choice: ");
        scanf("%i", &taskNumber);
        switch (taskNumber) {
            case 1:
                solution1(array, 10);
                break;
            case 2:
                solution2(array, 10);
                break;
            case 3:
                solution3(array, 10);
                break;
            case 4: {
                int maxLength[] = {100, 10000, 1000000};
                for (int i = 0; i < 3; i++) {
                    printf("\n%d elements in array\n", maxLength[i]);
                    array = malloc(sizeof(int) * maxLength[i]);
                    fillingArray(array, maxLength[i]);
                    solution1(array, maxLength[i]);
                    solution2(array, maxLength[i]);
                    solution3(array, maxLength[i]);
                    free(array);
                }
            }
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
