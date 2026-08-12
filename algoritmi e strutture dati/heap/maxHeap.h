//
// Created by Luca on 12/08/2026.
//
#include <iostream>
#include <stdexcept>

#ifndef ADT_HEAP_H
#define ADT_HEAP_H

class Heap{
private:
    int *a;
    int heapsize;
    int capacity;

    // calcolo degli indici
    int parent(int idx)const{
        return (idx-1) /2;
    }
    int left(int idx)const{
        return (2*idx)+1;

    }
    int right(int idx)const{
        return (2*idx)+2;
    }
    void maxHeapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;

        if( l < heapsize && a[l] > a[i])
            largest = l;

        if( r < heapsize && a[r] > a[largest])
            largest = r;

        if( largest != i ){
            int temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            maxHeapify(largest);
        }
    };
    void buildMaxHeap(){
        for(int i = heapsize/2 -1; i >= 0 ; i --)
            maxHeapify(i);
    };

    void resize(){
        capacity = capacity*2;
        int *new_a = new int[capacity];

        for(int i = 0; i < heapsize;i ++){
            new_a[i] = a[i];
        }
        delete []a;
        a = new_a;
    }

public:
    // costruttore di default su con array vuoto inizialmente vuoto
    Heap(){
        a = new int[10];
        heapsize = 0;
        capacity = 10;
    }
    // costruzione a partire da un array esistente
    Heap(const int *arr, int dim){
        if(dim < 0){
            throw std::invalid_argument("Dimensione non valida");
        }
        if(dim > 0 && arr == nullptr){
            throw std::invalid_argument("Atrray non valido");
        }
        heapsize = dim;
        capacity = (dim < 10) ? 10 : dim;
        a = new int[capacity];
        // copio gli elementi nel nostro heap
        for(int i = 0; i < dim; i ++){
            a[i] = arr[i];
        }
        buildMaxHeap();
    }
    // costruttore copia
    Heap(const Heap &h){}
    Heap& operator=(const Heap &h){}
    ~Heap(){
        delete []a;
    }

    bool is_empty(){
        return heapsize == 0;
    }

    // ??shift up come funzione distinta??
    void insert_elem(int k){
        if(heapsize == capacity){
            resize();
        }
        int current = heapsize;
        a[heapsize] = k;
        heapsize++;

        while(current > 0 && a[current] > a[parent(current)]){

            int tmp = a[parent(current)];
            a[parent(current)] = a[current];
            a[current] = tmp;
            current = parent(current);
        }
    }

    int maxHeapExtractMax(){

        int max = maxHeapMaximum();
        a[0] = a[heapsize-1];
        heapsize = heapsize - 1;
        maxHeapify(0);
        return max;
    }

    int maxHeapMaximum(){
        if(is_empty())return 0;
        return a[0];}

    int get_size()const{
        return heapsize;
    }

    int get_capacity()const{
        return capacity;
    }

    void print_heap(){
        for(int i = 0; i < heapsize; i++){
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
    }

};

#endif //ADT_HEAP_H
