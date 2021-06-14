/**
 * Copyright by Dmitriy-Kozyrev on 14.06.2021
 */

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
        
            _mergeSort(arr, size);

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

            _quickSort(arr, size);
            
            return arr;
        }

        static T* heapSort(T* arr, int size) {
            verifyData(arr, size);

            int globalIndex = size - 1;
            
            while (globalIndex >= 0) {
                sortSubTree(&arr[0], 0, globalIndex + 1, 1, false);
                std::swap(arr[0], arr[globalIndex--]);
            }
            return arr;
        }

    private:

        static void verifyData(T* arr, int size) {
            if (arr == nullptr)
                throw std::invalid_argument("Pointer is null!");
            if (size < 0)
                throw std::invalid_argument("Array size must not be less than zero!");
        }

        static void _mergeSort(T* arr, int size) {
            if (size > 1) {
                /* Split into two parts */
                mergeSort(arr, size / 2);
                mergeSort(arr+(size / 2), size - (size / 2));

                T* buff = new T[size];

                int index = 0;
                int i = 0, j = size / 2;

                /* Merging */
                for (i, j; i < size / 2 && j < size;) {
                    if (arr[i] >= arr[j]) 
                        buff[index++] = arr[j++];
                    else if (arr[i] < arr[j]) 
                        buff[index++] = arr[i++];
                }

                /* if the first half has already been recorded and the second half is not yet */
                if (i == size / 2 && j != size )
                    for (j; j < size; ++j) 
                        buff[index++] = arr[j];
                /* else if the second half has already been recorded and the first half is not yet */
                else if (j == size && i != size / 2)
                    for (i; i < size / 2; ++i) 
                        buff[index++] = arr[i];  

                for (int i = 0; i < size; ++i) {
                    arr[i] = buff[i];
                }

                delete[] buff;
            }
        }

        static void _quickSort(T* arr, int size) {
            if (size > 1) {
                std::swap(arr[size / 2], arr[size-1]);
                int globalIndex = 0;
                //while(globalIndex < size - 1) {
                //    std:: cout << globalIndex << "! ";
                for (int i = globalIndex; i < size - 1; ++i) {
                        if (arr[i] <= arr[size-1])  
                            std::swap(arr[globalIndex++], arr[i]);
                }
                std::swap(arr[globalIndex], arr[size-1]);
                quickSort(arr, globalIndex);
                quickSort(arr + globalIndex, size - globalIndex);
                //}
            }
        }

        /*
         * parent - pointer to tree root 
         * index - index of parent 
         * treeSize - size of full tree
         * offset - offset to simulate a tree 
         * isLeftSubTreeForParent - flag for specifying the offset for the left and right subtree */
        static void sortSubTree(T* parent, int index, int treeSize, int offset, bool isLeftSubTreeForParent) {
            
            T *left = nullptr, *rigth = nullptr;

            int tempOffset = isLeftSubTreeForParent? offset * 2 : (offset * 2) - 1 ;

            /* if the root of the subtree has a right subtree */
            if (index+tempOffset < treeSize) {
                sortSubTree(parent+tempOffset, index + tempOffset, treeSize, tempOffset, true);
                left = parent + tempOffset;
                /* if the root of the subtree has a left subtree */
                if (index+tempOffset+1 < treeSize) {
                    sortSubTree(parent + tempOffset + 1, index + tempOffset + 1, treeSize, tempOffset + 1, false);
                    rigth = parent + tempOffset + 1;
                }
            }
            else return;

            /* The parent root must be larger than its descendants (if sorting in ascending order) */
            T* max = *parent > *left ? parent : left;
            if (rigth != nullptr)
                max = *max > *rigth ? max : rigth;
            
            std::swap(*parent, *max);
        }
};

#endif