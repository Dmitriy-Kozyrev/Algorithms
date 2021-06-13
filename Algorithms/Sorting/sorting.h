#ifndef SORTING_H
#define SORTING_H

#include "stdexcept"
#include <iostream>

using namespace std;

template<class T>
class Sorting {
    public:
        static T* bubbleSort(T* arr, int size) {
            verifyData(arr, size);
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size-i-1; ++j) {
                    if (arr[j] > arr[j+1])
                        std::swap(arr[j], arr[j+1]);
                }
            return arr;
        }

        static T* shakerSort(T* arr, int size) {
            verifyData(arr, size);

            int i = 0;
            while (i < size - i){
                for (int j = i; j < size - 1; ++j) {
                    if (arr[j] > arr[j+1])
                        std::swap(arr[j], arr[j+1]);
                }
                for (int j = size - 1; j > i; --j) {
                    if (arr[j] < arr[j-1])
                        std::swap(arr[j], arr[j-1]);
                }
                i++;
            }
            return arr;
        }

        static T* insertionSort(T* arr, int size) {
            verifyData(arr, size);

            for (int i = 1; i < size; ++i) {
                int key = i;
                for (int j = i - 1; j >= 0; --j) {
                    if (arr[key] < arr[j])
                        std::swap(arr[key--], arr[j]);
                    else break;
                }
            }
            return arr;
        }   

        static T* mergeSort(T* arr, int size) {
            verifyData(arr, size);
        
            if (size > 1) {
                mergeSort(arr, size / 2); 
                mergeSort(arr+(size / 2), size - (size / 2));

                T* buff = new T[size];

                int index = 0;
                int i = 0, j = size / 2;
                for (i, j; i < size / 2 && j < size;) {
                    if (arr[i] >= arr[j]) 
                        buff[index++] = arr[j++];
                    else if (arr[i] < arr[j]) 
                        buff[index++] = arr[i++];
                }

                if (i == size / 2 && j != size )
                    for (j; j < size; ++j) 
                        buff[index++] = arr[j];
                else if (j == size && i != size / 2)
                    for (i; i < size / 2; ++i) 
                        buff[index++] = arr[i];  

                for (int i = 0; i < size; ++i) {
                    arr[i] = buff[i];
                } 
                delete[] buff;
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
                    std::swap(arr[i], arr[min]);
            }
            return arr;
        }

        static T* quickSort(T* arr, int size) {
            verifyData(arr, size);

            if (size > 1) {
                std::swap(arr[size / 2], arr[size-1]);
                int globalIndex = 0;
                while(globalIndex < size - 1) {
                    for (int i = globalIndex; i < size - 1; ++i) {
                        if (arr[i] <= arr[size-1])  
                            std::swap(arr[globalIndex++], arr[i]);
                    }
                    std::swap(arr[globalIndex], arr[size-1]);
                    quickSort(arr, globalIndex);
                    quickSort(arr + globalIndex, size - globalIndex);
                }
            }
            
            return arr;
        }

        static T* heapSort(T* arr, int size) {
            verifyData(arr, size);

            int globalIndex = size - 1;
            
            while (globalIndex >= 0) {
                sortSubTree(&arr[0], 0, globalIndex + 1, 1, false);
                std::swap(arr[0], arr[globalIndex--]);
            }
            cout << endl;
            return arr;
        }

        static T* tournamentSort(T* arr, int size) {
            verifyData(arr, size);

            return arr;
        }

    private:

        static void verifyData(T* arr, int size) {
            if (arr == nullptr)
                throw std::invalid_argument("Pointer is null!");
            if (size < 0)
                throw std::invalid_argument("Array size must not be less than zero!");
        }

        static void sortSubTree(T* parent, int index, int treeSize, int offset, bool isLeftSubTreeForParent) {
            
            T* left = nullptr;T* rigth = nullptr;

            int tempOffset = isLeftSubTreeForParent? offset * 2 : (offset * 2) - 1 ;

            if (index+tempOffset < treeSize) {
                sortSubTree(parent+tempOffset, index + tempOffset, treeSize, tempOffset, true);
                left = parent + tempOffset;
                if (index+tempOffset+1 < treeSize) {
                    sortSubTree(parent + tempOffset + 1, index + tempOffset + 1, treeSize, tempOffset + 1, false);
                    rigth = parent + tempOffset + 1;
                }
                    
            }
            else return;

            T* max = *parent > *left ? parent : left;
            if (rigth != nullptr)
                max = *max > *rigth ? max : rigth;
            
            std::swap(*parent, *max);
        }
};

#endif