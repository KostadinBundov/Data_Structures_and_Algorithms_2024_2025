#pragma once

#include <iostream>

template<class T>
class LinkedDeque {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    LinkedDeque();

    LinkedDeque(const LinkedDeque& other);

    LinkedDeque(LinkedDeque&& other);

    LinkedDeque& operator=(const LinkedDeque& other);

    LinkedDeque& operator=(LinkedDeque&& other);

    ~LinkedDeque();

    void push_front(const T& element);

    void push_back(const T& element);

    void pop_front();

    void pop_back();

    const T& front() const;

    const T& back() const;

    size_t getSize() const;

    bool isEmpty() const;

    class Iterator {
    private:
        Node* element;
        friend class LinkedDeque;

    public:
        Iterator(Node* element) : element(element) { }

        T& operator*() { return element->data; }
        T* operator->() { return &element->data; }

        Iterator& operator++() {
            if (element) {
                element = element->next;
            }

            return *this;
        }

        Iterator operator++(int) {
            Iterator toReturn(*this);
            ++(*this);
            return toReturn;
        }

        Iterator& operator--() {
            if (element) {
                element = element->prev;
            }

            return *this;
        }

        Iterator operator--(int) {
            Iterator toReturn(*this);
            --(*this);
            return toReturn;
        }

        bool operator==(const Iterator& other) const { return element == other.element; }
        bool operator!=(const Iterator& other) const { return element != other.element; }
    };

    class ConstIterator {
    private:
        friend class LinkedDeque;
        Node* element;

    public:
        ConstIterator(Node* element) : element(element) { }

        const T& operator*() const { return element->data; }
        const T* operator->() const { return &element->data; }

        ConstIterator& operator++() {
            if (element) {
                element = element->next;
            }

            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator toReturn(*this);
            ++(*this);
            return toReturn;
        }

        ConstIterator& operator--() {
            if (element) {
                element = element->prev;
            }

            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator toReturn(*this);
            --(*this);
            return toReturn;
        }

        bool operator==(const ConstIterator& other) const { return element == other.element; }
        bool operator!=(const ConstIterator& other) const { return element != other.element; }
    };

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    Iterator emplace(const ConstIterator& it, const T& element);
    Iterator remove(const ConstIterator& it);


private:
    void free();

    void copyFrom(const LinkedDeque& other);

    void moveFrom(LinkedDeque&& other);
};

template<class T>
LinkedDeque<T>::LinkedDeque() = default;

template<class T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque& other) {
    copyFrom(other);
}

template<class T>
LinkedDeque<T>::LinkedDeque(LinkedDeque&& other) {
    moveFrom(std::move(other));
}

template<class T>
LinkedDeque<T>& LinkedDeque<T>::operator=(const LinkedDeque& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template<class T>
LinkedDeque<T>& LinkedDeque<T>::operator=(LinkedDeque&& other) {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template<class T>
LinkedDeque<T>::~LinkedDeque() {
    free();
}

template<class T>
void LinkedDeque<T>::push_front(const T& element) {
    Node* newNode = new Node{ element };

    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    size++;
}

template<class T>
void LinkedDeque<T>::push_back(const T& element) {
    Node* newNode = new Node{ element };

    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

template<class T>
void LinkedDeque<T>::pop_front() {
    if (isEmpty()) {
        throw std::runtime_error("The deque is empty!");
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* toDel = head;
        head = head->next;
        head->prev = nullptr;
        delete toDel;
    }

    size--;
}

template<class T>
void LinkedDeque<T>::pop_back() {
    if (isEmpty()) {
        throw std::runtime_error("The deque is empty!");
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* toDel = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete toDel;
    }

    size--;
}

template<class T>
const T& LinkedDeque<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("The deque is empty!");
    }

    return head->data;
}

template<class T>
const T& LinkedDeque<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("The deque is empty!");
    }

    return tail->data;
}

template<class T>
size_t LinkedDeque<T>::getSize() const {
    return size;
}

template<class T>
bool LinkedDeque<T>::isEmpty() const {
    return size == 0;
}

template<class T>
typename LinkedDeque<T>::Iterator LinkedDeque<T>::begin() { return Iterator(head); }

template<class T>
typename LinkedDeque<T>::Iterator LinkedDeque<T>::end() { return Iterator(nullptr); }

template<class T>
typename LinkedDeque<T>::ConstIterator LinkedDeque<T>::cbegin() const { return ConstIterator(head); }

template<class T>
typename LinkedDeque<T>::ConstIterator LinkedDeque<T>::cend() const { return ConstIterator(nullptr); }

template<class T>
typename LinkedDeque<T>::Iterator LinkedDeque<T>::emplace(const ConstIterator& it, const T& element) {
    if (it == cend()) {
        throw std::runtime_error("Invalid place");
    }

    if (it == cbegin()) {
        push_front(element);
        return begin();
    }
    else if (it.element == tail) {
        push_back(element);
        return Iterator(tail);
    }
    else {
        Node* toInsert = new Node(element);
        Node* curr = it.element;

        toInsert->next = curr;
        curr->prev->next = toInsert;
        toInsert->prev = curr->prev;
        curr->prev = toInsert;

        return Iterator(toInsert);
    }
}

template<class T>
typename LinkedDeque<T>::Iterator LinkedDeque<T>::remove(const ConstIterator& it) {
    Node* curr = it.element;

    if (!curr) {
        throw std::runtime_error("Trying to remove end iterator");
    }
    else if (curr == head) {
        pop_front();
        return begin();
    }
    else if (curr == tail) {
        pop_back();
        return end();
    }
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        Node* next = curr->next;

        delete curr;
        size--;

        return Iterator(next);
    }
}

template<class T>
void LinkedDeque<T>::free() {
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
void LinkedDeque<T>::copyFrom(const LinkedDeque& other) {
    Node* iter = other.head;

    while (iter) {
        push_back(iter->data);
        iter = iter->next;
    }
}

template<class T>
void LinkedDeque<T>::moveFrom(LinkedDeque&& other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
}