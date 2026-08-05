#include <iostream>
//
// Created by Luca on 05/08/2026.
//

/*
 *  da aggiungere le funzioni ricorsive della linkedlist
 */
#ifndef ADT_LINKEDLIST_H
#define ADT_LINKEDLIST_H

class LinkedList{

private:

    /*
     * struct node senza il puntatore al dato satellite
     */
    struct Node{
    int key;
    Node *next;
    };

    Node *head;
    int size;

    /*
     * ritorna un nuovo nodo
     */
    Node* create_node(int k){
        Node *newNode = new Node();
        newNode->key = k;
        newNode->next = nullptr;
        return newNode;
    }
public:

    /*
     * costruttori
     */
    LinkedList(): head(nullptr), size(0){}


    void print_list(){
        if(is_empty()) std::cout << "List is empty\n";
        else{
            Node *ptrlist = head;
            while(ptrlist){
                std::cout << ptrlist << ":" << ptrlist->key << "--> ";
                ptrlist = ptrlist->next;
            }
            std::cout <<"\n";
        }
    }
    /*
     * metodi di informazioni sullo stato della lista
     */
    bool is_empty()const{return size == 0;}
    int size_list()const{return size;}

    /*
     * metodi di ricerca e scorrimento
     */
    Node* last_node(){
        if(is_empty()) return head;

        Node *ptrlist = head;
        while(ptrlist->next != nullptr){
            ptrlist = ptrlist->next;
        }
        return ptrlist;
    }

    Node* node_at_index(int i){
        int idx = 1;
        Node *ptrlist = head;
        while(idx < i){
            ptrlist = ptrlist->next;
            idx++;
        }
        return ptrlist;
    }
    /*
     * metodi di inserimento di un elemento nella lista
     */

    void push_front(int k){
        Node *newNode = create_node(k);
        newNode->next = head;
        head = newNode;
        size++;
    }
    void push_back(int k){
        if(is_empty()) push_front(k);
        else{
            Node *newNode = create_node(k);
            Node *lastNode = last_node();
            lastNode->next = newNode;
            size++;
        }
    }
    // inserimento in una determinata posizione (se essa è valida)
    void insert_at_index(int pos,int k){
        if(pos > size) return;
        if(pos == size) {
            push_back(k);
            return;
        }
        if(pos == 0) {
            push_front(k);
            return;
        }
        Node* newNode = create_node(k);
        Node* previusNode = node_at_index(pos);
        Node* tmp = previusNode->next;
        previusNode->next = newNode;
        newNode->next = tmp;
        size++;
    }

    /*
     * metodi di rimozione
     */
    void pop_front(){
        if(is_empty())return;

        Node *toDelete = head;
        head = head->next;
        delete toDelete;
        size--;
    }
    void pop_back(){
        if (is_empty())return;

        Node *toDelete = head;
        Node *previusPtr = toDelete;
        while(toDelete->next){
            previusPtr = toDelete;
            toDelete = toDelete->next;
        }
        previusPtr->next = nullptr;
        size--;
        delete toDelete;
    }

    void remove(int k){
        if(is_empty()) return ;

        if(head->key == k){
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node *toDelete = head;
        Node *previusNode = head;
        while(toDelete != nullptr){
            if(toDelete->key == k){
                previusNode->next = toDelete->next;
                delete toDelete;
                size--;
                return;
            }
            previusNode = toDelete;
            toDelete = toDelete->next;
        }
    }
    // un clear poco efficiente che utilizza il pop_back()
    void clearn2(){
        if(is_empty())return;

        while(head != nullptr){
            pop_back();
        }
        head = nullptr;
    }

    void clear(){
        if(is_empty())return;

        Node *tmp = head;
        while(head != nullptr){
            tmp = head->next;
            delete head;
            head = tmp;
            size--;
        }
    }

    Node *front(){
        if(is_empty())return nullptr;

        Node *frontNode = head->next;
        return frontNode;
    }
    Node *back(){
        if(is_empty())return nullptr;

        Node *lastNode = last_node();
        return lastNode;
    }
};

#endif //ADT_LINKEDLIST_H
