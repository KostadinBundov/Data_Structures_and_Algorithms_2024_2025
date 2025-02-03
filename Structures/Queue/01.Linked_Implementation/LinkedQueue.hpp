#pragma once

#include <iostream>

template<class T>
class LinkedQueue {
private:
    struct Node {
        Node(T data) : data(data) { }
        T data;
        Node* next = nullptr;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

public:
    LinkedQueue() = default;
    LinkedQueue(const LinkedQueue& other);
    LinkedQueue(LinkedQueue&& other);
    LinkedQueue<T>& operator=(const LinkedQueue<T>& other);
    LinkedQueue<T>& operator=(LinkedQueue<T>&& other);
    ~LinkedQueue();

    void push(const T& element);
    void pop();
    T& front() const;

    size_t getSize() const;
    bool isEmpty() const;

private:
    void free();
    void copyFrom(const LinkedQueue<T>& other);
    void moveFrom(LinkedQueue<T>&& other);
};

template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other) {
    copyFrom(other);
}

template<class T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T>&& other) {
    moveFrom(std::move(other));
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other) {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    free();
}

template<class T>
void LinkedQueue<T>::push(const T& element) {
    Node* newNode = new Node(element);

    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

template<class T>
void LinkedQueue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("The queue is empty!");
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* toDel = head;
        head = head->next;
        delete toDel;
    }

    size--;
}

template<class T>
T& LinkedQueue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("The queue is empty!");
    }
    return head->data;
}

template<class T>
size_t LinkedQueue<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedQueue<T>::isEmpty() const {
    return size == 0;
}

template<class T>
void LinkedQueue<T>::free() {
    Node* iter = head;

    while (iter) {
        Node* toDel = iter;
        iter = iter->next;
        delete toDel;
    }

    head = tail = nullptr;
    size = 0;
}

template<class T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other) {
    if (other.isEmpty()) {
        return;
    }

    head = new Node(other.head->data);
    Node* iter = head;
    Node* otherIter = other.head->next;

    while (otherIter) {
        iter->next = new Node(otherIter->data);
        iter = iter->next;
        otherIter = otherIter->next;
    }

    tail = iter;
    size = other.size;
}

template<class T>
void LinkedQueue<T>::moveFrom(LinkedQueue<T>&& other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
}
