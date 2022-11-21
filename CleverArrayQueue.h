// NOTE: if you have not read the ArrayQueue implementation, you should probably do that first, comments in this implementation just go over the differences,
// not the base behavior

#ifndef CLEVER_ARRAY_QUEUE_H
#define CLEVER_ARRAY_QUEUE_H

#include "AbstractQueue.h"

// This is pretty much the same exact class as the other ArrayQueue implementation, but uses some clever arithmetic to make dequeueing constant time instead
// of linear.
template <class T>
class Queue : public AbstractQueue<T> {
public:
	Queue() : _head(0), _size(0), _capacity(10), _data(new T[10]) {}
	Queue(unsigned long initialCapacity) : _head(0), _size(0), _capacity(initialCapacity), _data(new T[initialCapacity]) {}

	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	void enqueue(const T& elem);
	void dequeue() throw(Error);
	const T& front() const throw(Error);
	const T& back() const throw(Error);
	bool empty() const;
	unsigned long size() const;
	void clear();

	~Queue();

private:
	unsigned long _head;
	unsigned long _size;
	unsigned long _capacity;
	T* _data;

	void _expand();
	void _shrink();
};

#include "CleverArrayQueue.hpp"

#endif