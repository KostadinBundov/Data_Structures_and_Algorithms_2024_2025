#pragma once

template<class T>
class Iterator {
public:
	Iterator(T* pointer);
	Iterator(T* pointer, int offset);

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	Iterator& operator++();
	Iterator& operator--();

	Iterator operator++(int);
	Iterator operator--(int);

	Iterator operator+(int offset) const;
	Iterator operator-(int offset) const;

	operator Const_Iterator<T>() const;

	int operator-(Iterator<T> other) const;

	bool operator==(const Iterator<T>& other) const;
	bool operator!=(const Iterator<T>& other) const;

private:
	T* pointer;
};

template<class T>
Iterator<T>::Iterator<T>(T* pointer) {
	this->pointer = pointer;
}

template<class T>
Iterator<T>::Iterator<T>(T* pointer, int offset) {
	this->pointer = pointer + offset;
}

template<class T>
T& Iterator<T>::operator*() {
	return *pointer;
}

template<class T>
const T& Iterator<T>::operator*() const {
	return *pointer;
}

template<class T>
T* Iterator<T>::operator->() {
	return pointer;
}

template<class T>
const T* Iterator<T>::operator->() const {
	return pointer;
}


template<class T>
Iterator<T>& Iterator<T>::operator++() {
	++pointer;
	return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator--() {
	--pointer;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int) {
	Iterator it = *this;
	++pointer;
	return it;
}

template<class T>
Iterator<T> Iterator<T>::operator--(int) {
	Iterator it = *this;
	--pointer;
	return it;
}

template<class T>
Iterator<T> Iterator<T>::operator+(int offset) const {
	return Iterator(pointer + offset);
}

template<class T>
Iterator<T> Iterator<T>::operator-(int offset) const {
	return Iterator(pointer - offset);
}

template<class T>
Iterator<T>::operator Const_Iterator<T>() const
{
	return Const_Iterator<T>(pointer);
}

template<class T>
int Iterator<T>::operator-(Iterator<T> other) const
{
	return pointer - other.pointer;
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
	return pointer == other.pointer;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const {
	return pointer != other.pointer;
}