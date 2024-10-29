#pragma once

template<class T>
class Const_Iterator {
public:
	Const_Iterator(T* pointer);
	Const_Iterator(T* pointer, int offset);

	const T& operator*() const;
	const T* operator->() const;

	int operator-(Const_Iterator<T> other) const;

	Const_Iterator operator-(int offset) const;
	Const_Iterator operator+(int offset) const;

	bool operator==(const Const_Iterator& other) const;
	bool operator!=(const Const_Iterator& other) const;

private:
	T* pointer;
};

template<class T>
Const_Iterator<T>::Const_Iterator<T>(T* pointer) : pointer(pointer) {
}

template<class T>
Const_Iterator<T>::Const_Iterator<T>(T* pointer, int offset) : pointer(pointer + offset) {
}

template<class T>
const T& Const_Iterator<T>::operator*() const {
	return *pointer;
}

template<class T>
const T* Const_Iterator<T>::operator->() const {
	return pointer;
}

template<class T>
Const_Iterator<T> Const_Iterator<T>::operator+(int offset) const {
	return Const_Iterator(pointer + offset);
}

template<class T>
Const_Iterator<T> Const_Iterator<T>::operator-(int offset) const {
	return Const_Iterator(pointer - offset);
}

template<class T>
int Const_Iterator<T>::operator-(Const_Iterator<T> other) const
{
	return pointer - other.pointer;
}

template<class T>
bool Const_Iterator<T>::operator==(const Const_Iterator& other) const {
	return pointer == other.pointer;
}

template<class T>
bool Const_Iterator<T>::operator!=(const Const_Iterator& other) const {
	return pointer != other.pointer;
}