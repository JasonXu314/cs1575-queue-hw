template <class T>
Queue<T>::Node::Node(const Node& other) : _data(other._data) {
	if (other._next == NULL) {
		_next = NULL;
	} else {
		_next = new Node(*other._next);
	}
}

template <class T>
Queue<T>::Node::Node(const Node* other) : _data(other->_data) {
	if (other->_next == NULL) {
		_next = NULL;
	} else {
		_next = new Node(other->_next);
	}
}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : _size(other._size) {
	if (other._head == NULL) {
		_head = NULL;
		_tail = NULL;
	} else {
		// always remember to deep copy!
		_head = new Node(other._head->_data, NULL);

		Node *current = _head, *otherCurrent = other._head->_next;

		while (otherCurrent != NULL) {
			current->_next = new Node(otherCurrent->_data, NULL);
			current = current->_next;
			otherCurrent = otherCurrent->_next;
		}

		_tail = current;
	}
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	// this is technically optional, but a good check for stupid users who do queue = queue for shits and giggles (among other legimate reasons)
	if (this != &other) {
		_size = other._size;

		if (other._head == NULL) {
			_head = NULL;
			_tail = NULL;
		} else {
			// always remember to deep copy!
			_head = new Node(other._head->_data, NULL);

			Node *current = _head, *otherCurrent = other._head->_next;

			while (otherCurrent != NULL) {
				current->_next = new Node(otherCurrent->_data, NULL);
				current = current->_next;
				otherCurrent = otherCurrent->_next;
			}

			_tail = current;
		}
	}

	return *this;
}

template <class T>
void Queue<T>::enqueue(const T& elem) {
	if (_head == NULL) {
		// if the queue is empty, we just make a new head
		_head = new Node(elem, NULL);
		_tail = _head;
	} else {
		// otherwise, we stick it on the end (remember to update the tail, otherwise your back will be messed up)
		_tail->_next = new Node(elem, NULL);
		_tail = _tail->_next;
	}

	_size++;
}

template <class T>
void Queue<T>::dequeue() throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	Node* temp = _head;
	_head = _head->_next;
	// remember to clean up after yourself :D
	delete temp;

	_size--;

	if (empty()) {
		// if the queue is now empty, we need to update the tail, otherwise stuff might break (honestly i dont think this is required, but im paranoid lol)
		_tail = NULL;
	}
}

template <class T>
const T& Queue<T>::front() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	return _head->_data;
}

template <class T>
const T& Queue<T>::back() const throw(Error) {
	if (empty()) {
		throw Error("Queue is empty");
	}

	// this is trivialized because we have tail, this would run in O(n) time if we didn't have tail, since we would need to iterate through the entire queue
	return _tail->_data;
}

template <class T>
bool Queue<T>::empty() const {
	// this could also be _head == NULL
	return _size == 0;
}

template <class T>
unsigned long Queue<T>::size() const {
	return _size;
}

template <class T>
void Queue<T>::clear() {
	while (!empty()) {
		dequeue();
	}
}

template <class T>
Queue<T>::~Queue() {
	clear();
}