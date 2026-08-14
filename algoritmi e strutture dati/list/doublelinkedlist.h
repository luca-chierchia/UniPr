#include <iostream>
//
// Created by Luca on 06/08/2026.
//

#ifndef ADT_DOUBLELINKEDLIST_H
#define ADT_DOUBLELINKEDLIST_H

class DoubleLinkedList {
private:
    struct Node {
        int key;
        int *sat; // tipo int per semplificare
        Node *prev;
        Node *next;
    };

    int listlen;
    Node *head;
    Node *tail;

    Node* create_node(int k, int sat_value = 42) {
        Node *newNode = new Node();

        newNode->sat = new int(sat_value);
        newNode->key = k;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        return newNode;
    }

public:

    DoubleLinkedList()
        : head(nullptr), tail(nullptr), listlen(0) {}

    DoubleLinkedList(const DoubleLinkedList &l) {
        head = nullptr;
        tail = nullptr;
        listlen = 0;

        Node *cursor = l.head;

        while (cursor != nullptr) {

            // copia anche il dato satellite
            Node *newNode =
                create_node(cursor->key, *(cursor->sat));

            if (tail == nullptr) {
                head = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
            }

            tail = newNode;
            cursor = cursor->next;
            listlen++;
        }
    }

    DoubleLinkedList& operator=(const DoubleLinkedList &l) {

        if (this == &l)
            return *this;

        clear();

        Node *cursor = l.head;

        while (cursor != nullptr) {

            // copia anche il dato satellite
            Node *newNode =
                create_node(cursor->key, *(cursor->sat));

            if (tail == nullptr) {
                head = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
            }

            tail = newNode;
            cursor = cursor->next;
            listlen++;
        }

        return *this;
    }

    ~DoubleLinkedList() {
        clear();
    }

    bool is_empty() {
        return listlen == 0;
    }

    void clear() {

        Node *cursor = head;

        while (cursor != nullptr) {

            Node *tmp = cursor->next;

            // prima elimino il satellite
            delete cursor->sat;

            // poi il nodo
            delete cursor;

            cursor = tmp;
        }

        head = nullptr;
        tail = nullptr;
        listlen = 0;
    }

    void push_front(int k) {

        Node *newNode = create_node(k);

        if (is_empty()) {

            head = newNode;
            tail = newNode;

            listlen++;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;

        listlen++;
    }

    void push_back(int k) {

        if (is_empty()) {
            push_front(k);
            return;
        }

        Node *newNode = create_node(k);

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;

        listlen++;
    }

    void pop_front() {

        if (is_empty())
            return;

        if (head == tail) {

            delete head->sat;
            delete head;

            head = nullptr;
            tail = nullptr;

            listlen--;
            return;
        }

        Node *tmp = head;

        head = head->next;
        head->prev = nullptr;

        delete tmp->sat;
        delete tmp;

        listlen--;
    }

    void pop_back() {

        if (is_empty())
            return;

        if (head == tail) {

            delete head->sat;
            delete head;

            head = nullptr;
            tail = nullptr;

            listlen--;
            return;
        }

        Node *tmp = tail;

        tail = tail->prev;
        tail->next = nullptr;

        delete tmp->sat;
        delete tmp;

        listlen--;
    }

    void pop_elem(int k) {

        if (is_empty())
            return;

        Node *cursor = head;

        while (cursor != nullptr) {

            if (cursor->key == k) {

                if (cursor->prev != nullptr) {
                    cursor->prev->next = cursor->next;
                }
                else {
                    // cursor era head
                    head = cursor->next;
                }

                if (cursor->next != nullptr) {
                    cursor->next->prev = cursor->prev;
                }
                else {
                    // cursor era tail
                    tail = cursor->prev;
                }

                delete cursor->sat;
                delete cursor;

                // mancava questo
                listlen--;

                return;
            }

            cursor = cursor->next;
        }
    }

    int* search(int k) {

        if (is_empty())
            return nullptr;

        Node *cursor = head;

        while (cursor != nullptr) {

            if (cursor->key == k) {
                return cursor->sat;
            }

            cursor = cursor->next;
        }

        return nullptr;
    }

    void insert_in(int k, int idx) {

        // aggiunto controllo idx negativo
        if (idx < 0 || idx > listlen)
            return;

        if (idx == 0) {
            push_front(k);
            return;
        }

        if (idx == listlen) {
            push_back(k);
            return;
        }

        Node *cursor = head;
        Node *prevNode = cursor;

        for (int i = 0; i < idx; i++) {
            prevNode = cursor;
            cursor = cursor->next;
        }

        Node *newNode = create_node(k);

        prevNode->next = newNode;
        newNode->prev = prevNode;

        newNode->next = cursor;
        cursor->prev = newNode;

        listlen++;
    }

    void print_list_debug() {

        if (is_empty()) {
            std::cout << "List is empty\n";
            return;
        }

        Node *cursor = head;

        while (cursor != nullptr) {

            std::cout
                << cursor->prev << "<--[prev]"
                << "[address:" << cursor
                << ", k:" << cursor->key
                << ", sat:" << *(cursor->sat)
                << "][next]-->" << cursor->next
                << " | ";

            cursor = cursor->next;
        }

        std::cout << "\n";
    }

    void print_list() {

        if (is_empty()) {
            std::cout << "List is empty\n";
            return;
        }

        Node *cursor = head;

        while (cursor != nullptr) {

            std::cout << ",k:" << cursor->key;

            cursor = cursor->next;
        }

        std::cout << "\n";
    }
};

#endif //ADT_DOUBLELINKEDLIST_H
