template <class T>
Queue<T>::Queue(const Queue<T>& other) : _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]) {
	// always remember to deep copy
	for (unsigned long i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	// this is technically optional, but a good check for stupid users who do queue = queue for shits and giggles (among other legimate reasons)
	if (this != &other) {
		delete[] _data;

		_size = other._size;
		_capacity = other._capacity;
		_data = new T[other._capacity];

		// always remember to deep copy (also line 17)
		for (unsigned long i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}

	return *this;
}

template <class T>
void Queue<T>::enqueue(const T& elem) {
	// if the queue is full, we'll have to make more space to input more items
	if (_size == _capacity) {
		_expand();
	}

	// if you dondon't like the post-increment operator inside the array access, you can do it afterwards :P
	_data[_size++] = elem;
	// _size++;
}

template <class T>
T Queue<T>::dequeue() throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	// find the first thing in the queue
	T temp = _data[0];

	// we'll have to shift all the elements to the left by 1
	for (unsigned long i = 0; i < _size - 1; i++) {
		_data[i] = _data[i + 1];
	}

	_size--;

	// this saves some space sometimes (nice to have, not absolutely necessary)
	if (_size < _capacity / 2) {
		// Note that I use strict < operator, since if we shrink the queue after a removal, and the user immediately inserts again, it'll waste a lot of
		// time. This way, we have some leeway.
		_shrink();
	}

	return temp;
}

template <class T>
T Queue<T>::front() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	return _data[0];
}

template <class T>
T Queue<T>::back() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	return _data[_size - 1];
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
	// we could technically reset the capacity and data stuff, but it's not strictly necessary, since just setting the size to 0 will make all residual data
	// inaccessible anyway.
}

template <class T>
void Queue<T>::_expand() {
	// a very simple way to manufacture space (note: does not break physics)
	_capacity = _capacity * 2;
	T* temp = new T[_capacity];

	// always remember to deep copy
	for (unsigned long i = 0; i < _size; i++) {
		temp[i] = _data[i];
	}

	// always remember to clean up :D
	delete[] _data;
	_data = temp;
}

template <class T>
void Queue<T>::_shrink() {
	// a very simple way to delete space (note: does not work on astrophysical bodies)
	_capacity = _capacity / 2;
	T* temp = new T[_capacity];

	// always remember to deep copy
	for (unsigned long i = 0; i < _size; i++) {
		temp[i] = _data[i];
	}

	// always remember to clean up :D
	delete[] _data;
	_data = temp;
}

template <class T>
Queue<T>::~Queue() {
	delete[] _data;
}