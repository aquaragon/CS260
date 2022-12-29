//
// Created by aiden on 5/18/2022.
//

#ifndef MAIN_CPP_RECSORTS_HPP
#define MAIN_CPP_RECSORTS_HPP

void heapify(int array[],int length, int index);
void heapSort(int array[], int array_length);

void mergeSort(int array[], int length);
void recMergeSort(int * array, int begin, int end);
void merge(int * array, int begin, int high, int mid);

void quickSort(int array[], int length);
void recQuickSort(int array[], int left, int right);
int partition(int array[], int left, int right);

int findNth(int array[], int length, int n);
void recFindNth(int array[], int left, int right, int n);
int Nthpartion(int array[], int left, int right, int n);


#endif //MAIN_CPP_RECSORTS_HPP
