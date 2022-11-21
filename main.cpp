#include <iostream>
#include <string>

#include "ArrayQueue.h"

using namespace std;

int main() {
	Queue<int> queue;

	cout << "Size: " << queue.size() << endl;

	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);

	cout << "Size: " << queue.size() << endl;

	cout << "Front: " << queue.front() << endl;
	cout << "Back: " << queue.back() << endl;

	cout << "Dequeue: " << queue.dequeue() << endl;
	cout << "Size: " << queue.size() << endl;

	Queue<int> copy(queue);

	cout << "Copy Size: " << copy.size() << endl;
	cout << "Front: " << copy.front() << endl;
	cout << "Back: " << copy.back() << endl;

	copy.clear();

	cout << "Copy Size: " << copy.size() << endl;
	cout << "Original Size: " << queue.size() << endl;

	try {
		cout << "Front: " << copy.front() << endl;
		cout << "Shit broke!" << endl;
	} catch (Error& e) {
		cout << "Error: " << e.getMsg() << " ^_^" << endl;
	}

	Queue<int> copy2;
	copy2 = queue;

	cout << "Copy 2 Size: " << copy2.size() << endl;
	cout << "Front: " << copy2.front() << endl;
	cout << "Back: " << copy2.back() << endl;

	copy2.clear();

	cout << "Copy 2 Size: " << copy2.size() << endl;
	cout << "Original Size: " << queue.size() << endl;

	return 0;
}