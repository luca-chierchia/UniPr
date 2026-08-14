//
// Created by ellech on 14/08/26.
//
#include <iostream>
#include "doubleLinkedList.h"

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H
class Hashtable {
private:
    DoubleLinkedList **ptr;
    int k;

    // h(x) = x mod k
    int hashing_f(int key) {
        return key % k;
    }

public:
    Hashtable(int d) {
        k = d;
        ptr = new DoubleLinkedList *[k];

        for (int i = 0; i < k ; i++) {
            ptr[i] = new DoubleLinkedList;
        }
    }
    ~Hashtable() {
        for (int i = 0; i < k ; i++) {
            ptr[i]->clear();
        }
        delete[] ptr;
        std::cout << "distruttore hashtable\n";
    }
    void insert(int key) {
       int value = hashing_f(key);
       ptr[value]->push_front(key);
    }
    void remove(int key) {
        int value = hashing_f(key);
        ptr[value]->pop_elem(key);
    }
    // ritorna il puntatore al dato satelite (int per semplcità)
    int* search(int key) {
        int value = hashing_f(key);
        int* ptr_sat = nullptr;
        ptr_sat = ptr[value]->search(key);
        return ptr_sat;

    }

    void print_debug() {
        for (int i = 0; i < k; i++) {
            std::cout << ptr[i] << "->" ;
            if(!ptr[i]->is_empty())
                ptr[i]->print_list();
            std::cout << "\n";
        }

    }

};
#endif //HASHTABLE_HASHTABLE_H
