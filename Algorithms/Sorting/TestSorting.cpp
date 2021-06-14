#include <iostream>
#include <ctime>
#include <cstring>

#include "sorting.h"

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl; 
}

void fillArray(int* arr, int size,int leftBoundary, int rigthBoundary) {
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        arr[i] = leftBoundary + rand() % rigthBoundary;
    }
}


void testSorting(int* arr, int size, int (*ptrToFunc(int*, int)), std::string nameSorting) {
    
    std::cout << nameSorting << std::endl;

    int* arrCopy = new int[size];
    memcpy(arrCopy, arr, size * sizeof(int));

    clock_t start, end;
    start = clock();
    ptrToFunc(arrCopy, size);
    end = clock();

    delete[] arrCopy;

    std::cout << "Time: " << ((double) end - start) / ((double) CLOCKS_PER_SEC) << std::endl << std::endl;
}

void testSortings(int count, int leftBoundary, int rigthBoundary) {
    int* arr = new int[count];
    fillArray(arr, count,  leftBoundary, rigthBoundary);

    testSorting(arr, count, &Sorting<int>::quickSort, "Quick sort:");
    testSorting(arr, count, &Sorting<int>::mergeSort, "Merge sort:");
    testSorting(arr, count, &Sorting<int>::selectionSort, "Selection sort:");
    testSorting(arr, count, &Sorting<int>::insertionSort, "Insertion sort:");
    testSorting(arr, count, &Sorting<int>::shakerSort, "Shaker sort:");
    testSorting(arr, count, &Sorting<int>::bubbleSort, "Bubble sort:");
    testSorting(arr, count, &Sorting<int>::heapSort, "Heap sort:");
    
    delete[] arr;
}

int main(int argc, char* argv[]) {

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            int count = std::atoi(argv[i]);
            std::cout << count << " elements:" << std::endl << std::endl;
            testSortings(count, 0, 100000);
        }
    }

    return 0;
}