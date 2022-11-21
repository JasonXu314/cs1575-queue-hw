#ifndef ABSTRACT_QUEUE_H
#define ABSTRACT_QUEUE_H

#include <string>

// Oops is a stupid name >:(
class Error {
public:
	Error(const std::string& msg) : errorMessage(msg) {}
	const std::string& getMsg() const { return errorMessage; }

private:
	// I hate m_ prefix
	std::string errorMessage;
};

template <class T>
class AbstractQueue {
public:
	virtual void enqueue(const T& elem) = 0;
	virtual T dequeue() throw(Error) = 0;
	virtual T front() const throw(Error) = 0;
	// Technically this method makes this data structure a DEQueue (Double-Ended Queue), but apparently Morales doesn't care.
	virtual T back() const throw(Error) = 0;
	virtual bool empty() const = 0;
	virtual unsigned long size() const = 0;
	virtual void clear() = 0;

	// This is also technically unnecessary, but since it was in your template code, I'm including it :P
	virtual ~AbstractQueue() {}
};

#endif