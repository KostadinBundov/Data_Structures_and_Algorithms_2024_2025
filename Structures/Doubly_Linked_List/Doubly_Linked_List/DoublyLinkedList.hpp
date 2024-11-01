#pragma once

template<class T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& data) : data(data) { }

        Node(const Node& other) {
            copyFrom(other);
        }

        Node(Node&& other) {
            moveFrom(std::move(other));
        }

        Node& operator=(const Node& other) {
            if (this != &other) {
                copyFrom(other);
            }

            return *this;
        }

        Node& operator=(Node&& other) {
            if (this != &other) {
                moveFrom(std::move(other));
            }

            return *this;
        }

        ~Node() {
            free();
        }

    private:
        void copyFrom(const Node& other) {
            data = other.data;
        }
        void moveFrom(Node&& other) {
            data = std::move(other.data);
        }
        void free() {
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

    void copyFrom(const DoublyLinkedList<T>& other);
    void moveFrom(DoublyLinkedList<T>&& other);
    void free();

public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList(DoublyLinkedList<T>&& other);

    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);
    ~DoublyLinkedList();

    void pushBack(const T& element);
    void pushBack(T&& element);

    void pushFront(const T& element);
    void pushFront(T&& element);

    void popBack();
    void popFront();

    void clear() { free(); }

    class DllIterator;
    class ConstDllIterator;

    void print() const;

    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    DllIterator insert(const T& element, ConstDllIterator it);
    DllIterator insert(T&& element, ConstDllIterator it);
    DllIterator remove(const DllIterator& it);

    const T& front() const;
    const T& back() const;

    T& front();
    T& back();

    DllIterator begin() { return DllIterator(*this, head); }
    DllIterator end() { return DllIterator(*this, nullptr); }
    ConstDllIterator cbegin() const { return ConstDllIterator(*this, head); }
    ConstDllIterator cend() const { return ConstDllIterator(*this, nullptr); }

    class DllIterator {
        friend class DoublyLinkedList;

    private:
        Node* ptr;
        DoublyLinkedList& list;

    public:
        DllIterator(DoublyLinkedList& list, Node* curr) : list(list), ptr(curr) {}

        T& operator*() { return ptr->data; }
        T* operator->() { return &ptr->data; }

        DllIterator& operator++() {
            if (ptr) {
                ptr = ptr->next;
            }

            return *this;
        }

        DllIterator operator++(int) {
            DllIterator copy(*this);
            ++(*this);
            return copy;
        }

        DllIterator& operator--() {
            if (ptr == nullptr) {
                ptr = list.tail;
            }
            else {
                ptr = ptr->prev;
            }
            return *this;
        }

        DllIterator operator--(int) {
            DllIterator copy(*this);
            --(*this);
            return copy;
        }

        bool operator==(const DllIterator& other) const { return ptr == other.ptr; }

        bool operator!=(const DllIterator& other) const { return ptr != other.ptr; }
    };

    class ConstDllIterator {

    private:
        Node* ptr;
        const DoublyLinkedList& list;

    public:
        friend class DoublyLinkedList;

        ConstDllIterator(const DllIterator& iter) : list(iter.list), ptr(iter.ptr) {}
        ConstDllIterator(const DoublyLinkedList& list, Node* curr = nullptr) : list(list), ptr(curr) {}

        const T& operator*() const { return ptr->data; }
        const T* operator->() const { return &ptr->data; }

        ConstDllIterator& operator++() {
            if (ptr) {
                ptr = ptr->next;
            }

            return *this;
        }

        ConstDllIterator operator++(int) {
            ConstDllIterator copy(*this);
            ++(*this);
            return copy;
        }

        ConstDllIterator& operator--() {
            if (ptr == nullptr) {
                ptr = list.tail;
            }
            else {
                ptr = ptr->prev;
            }
            return *this;
        }

        ConstDllIterator operator--(int) {
            ConstDllIterator copy(*this);
            --(*this);
            return copy;
        }

        bool operator==(const ConstDllIterator& other) const { return ptr == other.ptr; }

        bool operator!=(const ConstDllIterator& other) const { return ptr != other.ptr; }
    };
};

template<class T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {
    Node* curr = other.head;

    while (curr) {
        pushBack(curr->data);
        curr = curr->next;
    }

}

template<class T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList<T>&& other) {
    head = other.head;
    other.head = nullptr;

    tail = other.tail;
    other.tail = nullptr;

    size = other.size;
    other.size = 0;
}

template<class T>
void DoublyLinkedList<T>::free() {
    Node* iter = head;

    while (iter) {
        Node* curr = iter;
        iter = iter->next;
        delete curr;
    }

    head = tail = nullptr;
    size = 0;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) {
    copyFrom(other);
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {
    moveFrom(other);
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    free();
}

template<class T>
void DoublyLinkedList<T>::pushBack(const T& element) {
    Node* newNode = new Node(element);

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

template<class T>
void DoublyLinkedList<T>::pushBack(T&& element) {
    Node* newNode = new Node(std::move(element));

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size++;
}

template<class T>
void DoublyLinkedList<T>::pushFront(const T& element) {
    Node* newNode = new Node(element);

    if (!head) {
        head = tail = newNode;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    size++;
}

template<class T>
void DoublyLinkedList<T>::pushFront(T&& element) {
    Node* newNode = new Node(std::move(element));

    if (!head) {
        head = tail = newNode;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    size++;
}

template<class T>
void DoublyLinkedList<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("The list is empty!");
    }

    if (head->next == nullptr) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* previous = tail->prev;
        delete tail;
        tail = previous;
        tail->next = nullptr;
    }

    size--;
}

template<class T>
void DoublyLinkedList<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("The list is empty!");
    }

    if (head->next == nullptr) {
        delete head;
        head = tail = nullptr;
    }
    else {
        Node* next = head->next;
        delete head;
        head = next;
        head->prev = nullptr;
    }

    size--;
}

template<class T>
void DoublyLinkedList<T>::print() const {
    Node* iter = head;

    while (iter != nullptr) {
        std::cout << iter->data;

        if (iter != tail) {
            std::cout << "<->";
        }

        iter = iter->next;
    }
    std::cout << std::endl;
}

template<class T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(const T& element, ConstDllIterator it) {
    if (it == cbegin()) {
        pushFront(element);
        return begin();
    }
    else if (it == cend()) {
        pushBack(element);
        return DllIterator(tail);
    }
    else {
        Node* toAdd = new Node(element);
        Node* current = it.ptr;

        current->prev->next = toAdd;
        toAdd->prev = current->prev;

        toAdd->next = current;
        current->prev = toAdd;

        size++;

        return DllIterator(*this, toAdd);
    }
}

template<class T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(T&& element, ConstDllIterator it) {
    if (it == cbegin()) {
        pushFront(std::move(element));
        return begin();
    }
    else if (it == cend()) {
        pushBack(std::move(element));
        return DllIterator(*this, tail);
    }
    else {
        Node* newNode = new Node(std::move(element));
        Node* current = it.ptr;

        newNode->next = current;
        newNode->prev = current->prev;

        if (current->prev) {
            current->prev->next = newNode;
        }
        current->prev = newNode;

        size++;

        return DllIterator(*this,newNode);
    }
}

template<class T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::remove(const DllIterator& it) {
    if (it == begin()) {
        popFront();
        return begin();
    }
    else if (it == end()) {
        popBack();
        return end();
    }
    else {
        Node* curr = it.ptr;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        Node* next = curr->next;

        delete curr;
        size--;

        return DllIterator(*this, next);
    }
}

template<class T>
const T& DoublyLinkedList<T>::front() const {
    if (head == nullptr) {
        throw std::runtime_error("The list is empty!");
    }

    return head->data;
}

template<class T>
const T& DoublyLinkedList<T>::back() const {
    if (head == nullptr) {
        throw std::runtime_error("The list is empty!");
    }

    return tail->data;
}

template<class T>
T& DoublyLinkedList<T>::front() {
    if (head == nullptr) {
        throw std::runtime_error("The list is empty!");
    }

    return head->data;
}

template<class T>
T& DoublyLinkedList<T>::back() {
    if (head == nullptr) {
        throw std::runtime_error("The list is empty!");
    }

    return tail->data;
}