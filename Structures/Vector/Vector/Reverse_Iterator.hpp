#pragma once

template<class T>
class Reverse_Iterator {
public:
	Reverse_Iterator(T* pointer);
	Reverse_Iterator(T* pointer, int offset);

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	Reverse_Iterator& operator++();
	Reverse_Iterator& operator--();

	Reverse_Iterator operator++(int);
	Reverse_Iterator operator--(int);

	Reverse_Iterator operator+(int offset) const;
	Reverse_Iterator operator-(int offset) const;

	bool operator==(const Reverse_Iterator<T>& other) const;
	bool operator!=(const Reverse_Iterator<T>& other) const;

private:
	T* pointer;
};

template<class T>
Reverse_Iterator<T>::Reverse_Iterator<T>(T* pointer) {
	this->pointer = pointer;
}

template<class T>
Reverse_Iterator<T>::Reverse_Iterator<T>(T* pointer, int offset) {
	this->pointer = pointer + offset;
}

template<class T>
T& Reverse_Iterator<T>::operator*() {
	return *pointer;
}

template<class T>
const T& Reverse_Iterator<T>::operator*() const {
	return *pointer;
}

template<class T>
T* Reverse_Iterator<T>::operator->() {
	return pointer;
}

template<class T>
const T* Reverse_Iterator<T>::operator->() const {
	return pointer;
}


template<class T>
Reverse_Iterator<T>& Reverse_Iterator<T>::operator++() {
	--pointer;
	return *this;
}

template<class T>
Reverse_Iterator<T>& Reverse_Iterator<T>::operator--() {
	++pointer;
	return *this;
}

template<class T>
Reverse_Iterator<T> Reverse_Iterator<T>::operator++(int) {
	Iterator it = *this;
	--pointer;
	return it;
}

template<class T>
Reverse_Iterator<T> Reverse_Iterator<T>::operator--(int) {
	Iterator it = *this;
	++pointer;
	return it;
}

template<class T>
Reverse_Iterator<T> Reverse_Iterator<T>::operator+(int offset) const {
	return Iterator(pointer - offset);
}

template<class T>
Reverse_Iterator<T> Reverse_Iterator<T>::operator-(int offset) const {
	return Iterator(pointer + offset);
}

template<class T>
bool Reverse_Iterator<T>::operator==(const Reverse_Iterator<T>& other) const {
	return pointer == other.pointer;
}

template<class T>
bool Reverse_Iterator<T>::operator!=(const Reverse_Iterator<T>& other) const {
	return pointer != other.pointer;
}