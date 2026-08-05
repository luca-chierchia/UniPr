//
// Created by Luca on 21/07/2026.
//
#include "math.h"

#ifndef ALGORITMI_DI_ORDINAMENTO_HEAPSORT_H
#define ALGORITMI_DI_ORDINAMENTO_HEAPSORT_H

// Non prendo in considerazione la possibilità di finire fuori dal range dell'array
int parent(int i){return floor(i/2);};
int left(int i ){return (i*2)+1;};
int right(int i){return (i*2)+2;};

void maxHeapify(int* arr, int i, int heapsize){
    int l = left(i);
    int r = right(i);
    int largest = i;

    if( l < heapsize && arr[l] > arr[i])
        largest = l;

    if( r < heapsize && arr[r] > arr[largest])
        largest = r;

    if( largest != i ){
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr,largest,heapsize);
    }
};

void minHeapify(int *arr, int i, int heapsize){
    int l = left(i);
    int r = right(i);
    int smaller = i;

    if( l < heapsize && arr[l] < arr[i])
        smaller = l;

    if( r < heapsize && arr[r] < arr[smaller])
        smaller = r;

    if( smaller != i ){
        int temp = arr[i];
        arr[i] = arr[smaller];
        arr[smaller] = temp;
        minHeapify(arr,smaller,heapsize);
    }
};

void buildMaxHeap(int *arr, int n){
    int heapsize = n;
    for(int i = n/2; i >= 0 ; i --)
        maxHeapify(arr,i,n);
};
void buildMinHeap(int *arr, int n){
    int heapsize = n;
    for(int i = n/2; i >= 0 ; i --)
        minHeapify(arr,i,n);
};

void heapsort(int *arr, int n){
    int heapsize = n;
    buildMaxHeap(arr, n);
    for( int i = n-1 ; i > 0 ;  i--){
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        heapsize--;
        maxHeapify(arr,0,heapsize);

    }
}

int maxHeapMaximum(int *arr){return arr[0];}
int minHeapMimimum(int *arr){return arr[0];}

int maxHeapExtractMax(int *arr, int *heapsize){

    int max = maxHeapMaximum(arr);
    arr[0] = arr[*heapsize-1];
    *heapsize = *heapsize - 1;
    maxHeapify(arr,0,*heapsize);
    return max;
}
int minHeapExtractMin(int *arr, int *heapsize){

    int min = minHeapMimimum(arr);
    arr[0] = arr[*heapsize-1];
    *heapsize = *heapsize - 1;
    maxHeapify(arr,0,*heapsize);
    return min;
}


// in questo caso int x è uguale ad un valore interno all'array che noi consideriamo chiave
void maxHeapIncreaseKey(int *arr, int i, int k){
    if (k < arr[i])
        return;  // la nuova chiave deve essere >= a quella attuale

    arr[i] = k;
    while (i > 0 && arr[parent(i)] < arr[i]) {
        int temp = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp;
        i = parent(i);
    }
}
#endif //ALGORITMI_DI_ORDINAMENTO_HEAPSORT_H
