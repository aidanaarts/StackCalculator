#include<iostream>

using namespace std;

template<class T>
struct node {
    T data;
    node<T> *nxt;
};

template<class T>
struct myStack {
    node<T> *head;
    myStack() {
        head = NULL;
    }
    void push(T x) {
        node<T> *n = new node<T>();
        n->data = x;
        n->nxt = head;
        head = n;
    }

    T pop(int *empty) {
        if (head == NULL) {
            *empty = 1;
            return 0;
        }
        *empty = 0;
        node<T> *tmp = head;
        head = head->nxt;
        T x = tmp->data;
        delete (tmp);
        return x;
    }

    char top() {
        if (head == NULL) {
            return 0;
        }
        return head->data;
    }
};
