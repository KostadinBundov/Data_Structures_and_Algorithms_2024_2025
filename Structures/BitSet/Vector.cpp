#include "Vector.h"

template <class Allocator>
void Vector<Allocator>::copyFrom(const Vector<Allocator>& other) {
	//data = static_cast<bool*>(operator new (other._capacity * sizeof(bool)));

	data = _allocator.allocate(other._capacity);

	for (int i = 0; i < other._capacity; i++) {
		//new (&data[i]) bool(other.data[i]);
		_allocator.construct(&data[i], other.data[i]);
	}

	_size = other._size;
	_capacity = other._capacity;
}

template <class Allocator>
void Vector<Allocator>::moveFrom(Vector<Allocator>&& other) {
	data = other.data;
	other.data = nullptr;

	_size = other._size;
	other._size = 0;

	_capacity = other._capacity;
	other._capacity = 0;
}

template <class Allocator>
void Vector<Allocator>::free() {
	for (int i = 0; i < _capacity; i++) {
		_allocator.destroy(&data[i]);
	}

	//operator delete (data, _capacity * sizeof(bool));

	_allocator.deallocate(data, _capacity);

	_size = 0;
	_capacity = 0;
	data = nullptr;
}

template <class Allocator>
size_t Vector<Allocator>::calculateCapacity() const {
	return _capacity + Constants::GROWTH_FACTOR;
}

template <class Allocator>
Vector<Allocator>::Vector(size_t size) {
	_capacity = size / Constants::BUCKET_SIZE + 1;
	this->_size = size;
	data = _allocator.allocate(_capacity);
	//data = static_cast<bool*>(operator new (_capacity * sizeof(bool)));
}

template <class Allocator>
Vector<Allocator>::Vector(size_t size, uint8_t initial) {
	initial = initial ? 0b11111111 : 0b00000000;

	_capacity = size / Constants::BUCKET_SIZE + 1;
	this->_size = size;

	data = _allocator.allocate(_capacity);

	for (int i = 0; i < _capacity; i++) {
		//new (&data[i]) bool(initial);
		_allocator.construct(&data[i], initial);
	}
}

template <class Allocator>
Vector<Allocator>::Vector(const Vector<Allocator>& other) {
	copyFrom(other);
}

template <class Allocator>
Vector<Allocator>::Vector(Vector<Allocator>&& other) noexcept {
	moveFrom(std::move(other));
}

template <class Allocator>
Vector<Allocator>& Vector<Allocator>::operator=(const Vector<Allocator>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <class Allocator>
Vector<Allocator>& Vector<Allocator>::operator=(Vector<Allocator>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <class Allocator>
Vector<Allocator>::~Vector() {
	free();
}

template <class Allocator>
size_t Vector<Allocator>::size() const
{
	return _size;
}

template <class Allocator>
size_t Vector<Allocator>::capacity() const
{
	return _capacity * Constants::BUCKET_SIZE;
}

template <class Allocator>
bool Vector<Allocator>::isEmpty() const {
	return _size == 0;
}

template <class Allocator>
void Vector<Allocator>::push_back(bool value) {
	if (_size >= _capacity * Constants::BUCKET_SIZE) {
		resize(calculateCapacity());
	}

	(*this)[_size] = value;
	_size++;
}

template <class Allocator>
void Vector<Allocator>::pop_back() {
	if (!isEmpty()) {
		_size--;
	}
}

template <class Allocator>
void Vector<Allocator>::pop_front() {
	remove(begin());
}

template <class Allocator>
void Vector<Allocator>::insert(ConstIterator it, bool value) {
	if (_size >= _capacity * Constants::BUCKET_SIZE) {
		size_t newCapacity = calculateCapacity();
		resize(newCapacity);
	}

	if (_size == 0 || it == cend()) {
		push_back(value);
	}
	else {
		unsigned index = (it.reference.bucket - data) * Constants::BUCKET_SIZE + it.reference.bitIndex;

		for (int i = _size; i > index; --i) {
			bool value = (*this)[i - 1];
			(*this)[i] = value;
		}

		(*this)[index] = value;
		_size++;
	}
}

template <class Allocator>
void Vector<Allocator>::remove(Iterator it) {
	if (isEmpty()) {
		return;
	}

	unsigned index = (it.reference.bucket - data) * Constants::BUCKET_SIZE + it.reference.bitIndex;

	for (int i = index; i < _size - 1; i++) {
		bool value = (*this)[i + 1];
		(*this)[i] = value;
	}

	_size--;
}

template <class Allocator>
typename Vector<Allocator>::BitReference Vector<Allocator>::operator[](int index) {
	unsigned bucketIndex = index / Constants::BUCKET_SIZE;
	unsigned bitIndex = index % Constants::BUCKET_SIZE;

	return BitReference(&data[bucketIndex], bitIndex);
}

template <class Allocator>
const typename Vector<Allocator>::BitReference Vector<Allocator>::operator[](int index) const {
	unsigned bucketIndex = index / Constants::BUCKET_SIZE;
	unsigned bitIndex = index % Constants::BUCKET_SIZE;

	return BitReference(&data[bucketIndex], bitIndex);
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::begin() {
	return Iterator({ &data[0], 0 });
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::end() {
	return Iterator({ &data[_size / Constants::BUCKET_SIZE], _size % Constants::BUCKET_SIZE });
}

template <class Allocator>
typename Vector<Allocator>::ConstIterator Vector<Allocator>::cbegin() const {
	return ConstIterator({ &data[0], 0 });
}

template <class Allocator>
typename Vector<Allocator>::ConstIterator Vector<Allocator>::cend() const {
	return ConstIterator({ &data[_size / Constants::BUCKET_SIZE], _size % Constants::BUCKET_SIZE });
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::rbegin()
{
	return ReverseIterator({ &data[(_size - 1) / Constants::BUCKET_SIZE], (_size - 1) % Constants::BUCKET_SIZE });
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::rend()
{
	return ReverseIterator({ &data[0] - 1, Constants::BUCKET_SIZE - 1 });
}

template <class Allocator>
void Vector<Allocator>::resize(size_t newCapacity) {
	if (newCapacity <= _capacity) {
		return;
	}

	//bool* resizedData = static_cast<bool*>(operator new (newCapacity * sizeof(bool)));
	uint8_t* resizedData = _allocator.allocate(newCapacity);

	for (size_t i = 0; i < _capacity; i++) {
		//new (&resizedData[i]) bool(data[i]);
		_allocator.construct(&resizedData[i], std::move(data[i]));
	}

	_allocator.construct(&resizedData[_capacity], 0);

	_allocator.deallocate(data, _capacity);
	//operator delete (data, _capacity * sizeof(bool));

	data = resizedData;
	_capacity = newCapacity;
}

template <class Allocator>
typename Vector<Allocator>::BitReference& Vector<Allocator>::BitReference::operator=(bool value) {
	unsigned mask = 1 << bitIndex;

	if (value) {
		*bucket |= mask;
	}
	else {
		*bucket &= ~mask;
	}

	return *this;
}

template <class Allocator>
Vector<Allocator>::BitReference::operator bool() const {
	unsigned mask = 1 << bitIndex;
	return ((*bucket) & mask) == mask;
}

template <class Allocator>
typename Vector<Allocator>::BitReference Vector<Allocator>::Iterator::operator*() {
	return reference;
}

template <class Allocator>
typename Vector<Allocator>::BitReference* Vector<Allocator>::Iterator::operator->()
{
	return &reference;
}

template <class Allocator>
typename Vector<Allocator>::Iterator& Vector<Allocator>::Iterator::operator++() {
	reference.bitIndex++;

	if (reference.bitIndex >= Constants::BUCKET_SIZE) {
		reference.bucket++;
		reference.bitIndex = 0;
	}

	return *this;
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::Iterator::operator++(int) {
	Iterator copy = *this;
	++(*this);
	return copy;
}

template <class Allocator>
typename Vector<Allocator>::Iterator& Vector<Allocator>::Iterator::operator--() {
	if (reference.bitIndex == 0) {
		reference.bucket--;
		reference.bitIndex = Constants::BUCKET_SIZE - 1;
	}
	else {
		reference.bitIndex--;
	}

	return *this;
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::Iterator::operator--(int) {
	Iterator copy = *this;
	--(*this);
	return copy;
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::Iterator::operator+(int n) const {
	Iterator it = *this;

	it.reference.bitIndex += n;

	if (reference.bitIndex >= Constants::BUCKET_SIZE) {
		it.reference.bucket += n / Constants::BUCKET_SIZE + 1;
		it.reference.bitIndex %= Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
typename Vector<Allocator>::Iterator Vector<Allocator>::Iterator::operator-(int n) const {
	Iterator it = *this;
	it.reference.bitIndex -= n;

	if (reference.bitIndex < 0) {
		it.reference.bucket -= n / Constants::BUCKET_SIZE + 1;
		it.reference.bitIndex = abs(it.reference.bitIndex) % Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
bool Vector<Allocator>::Iterator::operator==(const Iterator& other) const {
	return reference.bucket == other.reference.bucket && reference.bitIndex == other.reference.bitIndex;
}

template <class Allocator>
bool Vector<Allocator>::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

template <class Allocator>
const typename Vector<Allocator>::BitReference Vector<Allocator>::ConstIterator::operator*() const {
	return reference;
}

template <class Allocator>
const typename Vector<Allocator>::BitReference* Vector<Allocator>::ConstIterator::operator->() const {
	return &reference;
}

template <class Allocator>
typename Vector<Allocator>::ConstIterator Vector<Allocator>::ConstIterator::operator+(int n) const {
	ConstIterator it = *this;

	it.reference.bitIndex += n;

	if (reference.bitIndex >= Constants::BUCKET_SIZE) {
		it.reference.bucket += n / Constants::BUCKET_SIZE + 1;
		it.reference.bitIndex %= Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
typename Vector<Allocator>::ConstIterator Vector<Allocator>::ConstIterator::operator-(int n) const {
	ConstIterator it = *this;
	it.reference.bitIndex -= n;

	if (reference.bitIndex < 0) {
		it.reference.bucket -= n / Constants::BUCKET_SIZE + 1;
		it.reference.bitIndex = abs(it.reference.bitIndex) % Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
bool Vector<Allocator>::ConstIterator::operator==(const ConstIterator& other) const {
	return reference.bucket == other.reference.bucket && reference.bitIndex == other.reference.bitIndex;
}

template <class Allocator>
bool Vector<Allocator>::ConstIterator::operator!=(const ConstIterator& other) const {
	return !(*this == other);
}

template <class Allocator>
typename Vector<Allocator>::BitReference Vector<Allocator>::ReverseIterator::operator*() {
	return reference;
}

template <class Allocator>
typename Vector<Allocator>::BitReference* Vector<Allocator>::ReverseIterator::operator->() {
	return &reference;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator& Vector<Allocator>::ReverseIterator::operator++() {
	if (reference.bitIndex == 0) {
		reference.bucket--;
		reference.bitIndex = Constants::BUCKET_SIZE - 1;
	}
	else {
		reference.bitIndex--;
	}

	return *this;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::ReverseIterator::operator++(int) {
	ReverseIterator it = *this;
	++(*this);
	return it;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator& Vector<Allocator>::ReverseIterator::operator--() {
	reference.bitIndex++;

	if (reference.bitIndex >= Constants::BUCKET_SIZE) {
		reference.bucket++;
		reference.bitIndex = 0;
	}

	return *this;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::ReverseIterator::operator--(int) {
	ReverseIterator it = *this;
	--(*this);
	return it;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::ReverseIterator::operator+(int n) const {
	ReverseIterator it = *this;
	it.reference.bitIndex -= n;

	while (it.reference.bitIndex < 0) {
		it.reference.bucket--;
		it.reference.bitIndex += Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
typename Vector<Allocator>::ReverseIterator Vector<Allocator>::ReverseIterator::operator-(int n) const {
	ReverseIterator it = *this;
	it.reference.bitIndex += n;

	while (it.reference.bitIndex >= Constants::BUCKET_SIZE) {
		it.reference.bucket++;
		it.reference.bitIndex -= Constants::BUCKET_SIZE;
	}

	return it;
}

template <class Allocator>
bool Vector<Allocator>::ReverseIterator::operator==(const ReverseIterator& other) const {
	return reference.bucket == other.reference.bucket && reference.bitIndex == other.reference.bitIndex;
}

template <class Allocator>
bool Vector<Allocator>::ReverseIterator::operator!=(const ReverseIterator& other) const {
	return !(*this == other);
}

template class Vector<>;