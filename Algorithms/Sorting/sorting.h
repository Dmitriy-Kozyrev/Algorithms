#ifndef SORTING_H
#define SORTING_H

#include "stdexcept"

template<class T>
class Sorting {
    public:
        static T* bubbleSort(T* arr, int size) {
            verifyData(arr, size);

            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size-i-1; ++j) {
                    if (arr[j] > arr[j+1])
                        swap(&arr[j], &arr[j+1]);
                }
            return arr;
        }

        static T* shakerSort(T* arr, int size);

        static T* insertionSort(T* arr, int size) {
            verifyData(arr, size);

            for (int i = 1; i < size; ++i) {
                int key = i;
                for (int j = i - 1; j >= 0; --j) {
                    if (arr[key] < arr[j])
                        swap(&arr[key--], &arr[j]);
                    else break;
                }
            }
            return arr;
        }   

        static T* mergeSort(T* arr, int size) {
            if (size > 1) {
                mergeSort(arr, size / 2);
                mergeSort(arr+(size/2), size - (size/2));

                for (int i = 0, j = size/2; i < size/2 && j < size;) {
                    
                }
            }
            return arr;
        }

        static T* selectionSort(T* arr, int size) {
            verifyData(arr, size);

            int min;
            for (int i = 0; i < size - 1; ++i) {
                min = i;
                for (int j = i + 1; j < size; ++j) {
                    if (arr[j] < arr[min]) 
                        min = j;
                }
                if (min != i)
                    swap(&arr[i], &arr[min]);
            }
            return arr;
        }

        static T* quickSort(T* arr, int size);

        static T* heapSort(T* arr, int size);

        static T* tournamentSort(T* arr, int size);

    private:
        static void swap(T* first, T* second) {
            T temp = *first;
            *first = *second;
            *second = temp;
        }

        static void verifyData(T* arr, int size) {
            if (arr == nullptr)
                throw std::invalid_argument("Pointer is null!");
            if (size < 0)
                throw std::invalid_argument("Array size must not be less than zero!");

        }
};

#endif