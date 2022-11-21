#ifndef QUEUE_H
#define QUEUE_H

#include "AbstractQueue.h"

template <class T>
class Queue : public AbstractQueue<T> {
public:
	Queue() : _size(0), _capacity(10), _data(new T[10]) {}
	Queue(unsigned long initialCapacity) : _size(0), _capacity(initialCapacity), _data(new T[initialCapacity]) {}

	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	void enqueue(const T& elem);
	T dequeue() throw(Error);
	T front() const throw(Error);

	// Technically this method makes this data structure a DEQueue (Double-Ended Queue), but apparently Morales doesn't care.
	T back() const throw(Error);
	bool empty() const;
	unsigned long size() const;
	void clear();

	~Queue();

private:
	unsigned long _size;
	unsigned long _capacity;
	T* _data;

	// When the queue is full, we'll have to make more space to input more items
	void _expand();

	// This method is optional, but i like it because why not
	void _shrink();
};

#include "Queue.hpp"

#endif