#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "AbstractQueue.h"

template <class T>
class Queue : public AbstractQueue<T> {
public:
	Queue() : _size(0), _head(NULL), _tail(NULL) {}

	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	void enqueue(const T& elem);
	void dequeue() throw(Error);
	const T& front() const throw(Error);

	// Technically this method makes this data structure a DEQueue (Double-Ended Queue), but apparently Morales doesn't care.
	const T& back() const throw(Error);
	bool empty() const;
	unsigned long size() const;
	void clear();

	~Queue();

private:
	class Node {
	public:
		Node(const T& data, Node* next) : _data(data), _next(next) {}

		// copy constructors here purely for convenience's sake (will implement automatic deep copy via recursion)
		Node(const Node& other);
		Node(const Node* other);
		// NOTE: these don't actually do anything, since this is a DEQueue, and we have to get the tail anyway, but if this were just a regular Queue, these
		// would make copying more convenient

		T _data;
		Node* _next;
	};

	unsigned long _size;
	Node* _head;
	Node* _tail;
};

#include "LinkedQueue.hpp"

#endif