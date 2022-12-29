//
// Created by aiden on 5/18/2022.
//
#include "recSorts.hpp"
#include <array>

void heapify(int array[], int length, int root)
{

    // Initialize largest as root
    int largest = root;

    // left child = 2*i + 1
    int left = 2 * root + 1;

    // right child = 2*i + 2
    int right = 2 * root + 2;

    // If left child is larger than root
    if (left < length && array[left] > array[largest])
    {
        largest = left;
    }
    // If right child is larger than largest
    if (right < length && array[right] > array[largest])
    {
        largest = right;
    }
    // If largest is not root
    if (largest != root) {
        int temp = array[root];
        array[root] = array[largest];
        array[largest] = temp;
        // Recursively heapify the rest of the tree
        heapify(array, length, largest);
    }
}

void heapSort(int array[], int length)
{
    for (int i = length / 2 - 1; i >= 0; i--) //First heapify the array
    {
        heapify(array, length, i);
    }
    for (int i = length - 1; i > 0; i--) //Now that the array is heapified we can take the value at root and place it at the end making an ascending array
    {
        //swap the root with the length -1 value
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        //array needs to be re-heaped with new length because the highest was moved to the end of the array
        heapify(array, i, 0);
    }
}

void merge(int * array, int begin, int end, int mid)
{
    int i,j,k,c[50];
    i = begin;
    k=begin;
    j= mid + 1;
    while(i <= mid && j <= end)
    {
        if (array[i] < array[j])
        {
            c[k] = array[i];
            k++;
            i++;
        }else
        {
            c[k] = array[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = array[i];
        k++;
        i++;
    }
    while (j <= end)
    {
        c[k] = array[j];
        k++;
        j++;
    }
    for (i = begin; i < k; i++)
    {
        array[i] = c[i];
    }
}

void recMergeSort(int * array, int begin, int end)
{
    int mid;
    if( begin < end)
    {
        mid = (begin+end)/2;
        recMergeSort(array,begin,mid);
        recMergeSort(array,mid+1,end);
        merge(array,begin,end,mid);
    }
}

void mergeSort(int array[], int length)
{
    recMergeSort(array,0,length-1);
}

void quickSort(int array[], int length)
{
    recQuickSort(array, 0, length-1);
}

void recQuickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(array,low,high);
        recQuickSort(array,low, pivot - 1);
        recQuickSort(array, pivot + 1, high);
    }
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);

    for(int j = low; j < high; j++)
    {
        if(array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i+1] = array[high];
    array[high] = temp;
    return (i+1);
}

int findNth(int array[], int length, int n)
{
    recFindNth(array, 0,length-1, n);
    return array[n];
}

void recFindNth(int array[], int left, int right, int n)
{
    if (left < right)
    {
        int pivot = Nthpartion(array,left,right,n);
        if(pivot == n)
        {
            return;
        }
        recFindNth(array,left, pivot - 1,n);
        recFindNth(array, pivot + 1, right,n);
    }
}

int Nthpartion(int array[],int left, int right, int n)
{
    int pivot = array[right];
    if(pivot == n)
    {
        return pivot;
    }
    int i = (left - 1);

    for(int j = left; j < right; j++)
    {
        if(array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i+1] = array[right];
    array[right] = temp;
    return (i+1);
}