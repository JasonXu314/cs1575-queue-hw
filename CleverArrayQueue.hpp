// NOTE: if you have not read the ArrayQueue implementation, you should probably do that first, comments in this implementation just go over the differences,
// not the base behavior

// We can set the head to 0 here, since we're creating a whole new queue (see enqueue/dequeue/front/back methods for how head works)
template <class T>
Queue<T>::Queue(const Queue<T>& other) : _head(0), _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]) {
	for (unsigned long i = 0; i < _size; i++) {
		_data[i] = other._data[(other._head + i) % _capacity];
	}
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		delete[] _data;

		_head = 0;
		_size = other._size;
		_capacity = other._capacity;
		_data = new T[other._capacity];

		for (unsigned long i = 0; i < _size; i++) {
			_data[i] = other._data[(other._head + i) % _capacity];
		}
	}

	return *this;
}

template <class T>
void Queue<T>::enqueue(const T& elem) {
	if (_size == _capacity) {
		_expand();
	}

	// technically i can put post-increment operator in there i think, but i dont have the confidence to do it here lul
	// this is part of the clever arithmetic mentioned earlier; basically, as the head marches towards the end of the array, we mod by capacity to "wrap
	// around" to the front of the array again, allowing the dequeue operation to just march the head foward
	_data[(_head + _size) % _capacity] = elem;
	_size++;
}

template <class T>
void Queue<T>::dequeue() throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	T temp = _data[0];

	// move the head forward, making the next thing in the queue the first thing in the queue, effectively deleting the current first element. mod by capacity
	// because we don't want to walk off the end of the array
	// This way of dequeueing is constant time, but a bit harder to understand (think hard about how the enqueue, dequeue, and front methods work together)
	_head = (_head + 1) % _capacity;

	_size--;

	if (_size < _capacity / 2) {
		_shrink();
	}

	return temp;
}

template <class T>
const T& Queue<T>::front() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	return _data[0];
}

template <class T>
const T& Queue<T>::back() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	// again, mod by capacity so we don't walk off the end of the array, following the same logic as above (think "wrap-around")
	return _data[(_head + _size - 1) % _capacity];
}

template <class T>
bool Queue<T>::empty() const {
	return _size == 0;
}

template <class T>
unsigned long Queue<T>::size() const {
	return _size;
}

template <class T>
void Queue<T>::clear() {
	_size = 0;
	// might as well set head to 0, because we're clearing the queue anyway
	_head = 0;
}

template <class T>
void Queue<T>::_expand() {
	T* temp = new T[_capacity * 2];

	// we'll take this opportunity to reset the head to 0 (see line 112), since we're going to have to copy all the data anyway, this is why we can start the
	// loop at i = 0
	for (unsigned long i = 0; i < _size; i++) {
		temp[i] = _data[(_head + i) % _capacity];
	}

	delete[] _data;
	_head = 0;
	_capacity = _capacity * 2;
	_data = temp;
}

template <class T>
void Queue<T>::_shrink() {
	T* temp = new T[_capacity / 2];

	// we'll take this opportunity to reset the head to 0 (see line 128), since we're going to have to copy all the data anyway, this is why we can start the
	// loop at i = 0
	for (unsigned long i = 0; i < _size; i++) {
		temp[i] = _data[(_head + i) % _capacity];
	}

	delete[] _data;
	_head = 0;
	_capacity = _capacity / 2;
	_data = temp;
}

template <class T>
Queue<T>::~Queue() {
	delete[] _data;
}