#ifndef DEQ_H
#define DEQ_H
#include <stdlib.h>
#include <stdexcept>

template <typename T>
struct Node {
 	Node<T> *next;
 	Node<T> *prev;
 	T value;
};

template <typename T>
class Deque {
public:
  class Iterator {
  public:
  	Iterator(Node<T>*);
  	Iterator operator++();
    T& operator*();
  private:
  	Node<T> *cur;
  };
	Deque();
	bool isEmpty();
	int size();
	void addFirst(T);
	void addLast(T);
	T removeFirst();
	T removeLast();
	Deque<T>::Iterator iterator();
private:
	int _size;
	Node<T> *front;
	Node<T> *back;
};

// Receives the front node pointer from the deque.
// Construction is always constant time.
template <typename T>
Deque<T>::Iterator::Iterator(Node<T> *n) {
  cur = n;
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator++() {
  if (cur) {
    if (cur->prev) { cur = cur->prev; }
    return *this;
  }
}

template <typename T>
T& Deque<T>::Iterator::operator*() {
  if (cur) { return cur->value; }
}

template <typename T>
Deque<T>::Deque() {
	_size = 0;
	front = NULL;
	back = NULL;
}

template <typename T>
bool Deque<T>::isEmpty() {
	return (_size == 0);
}

template <typename T>
int Deque<T>::size() {
	return _size;
}

template <typename T>
void Deque<T>::addFirst(T val) {
	Node<T> *n = new Node<T>;
	n->value = val;
	n->next = NULL;
	n->prev = NULL;
	if (front) {
	  Node<T> *p = front;
		p->next = n;
		front = n;
		front->prev = p;
	}
	else {
		front = n;
		back = n;
	}
  _size++;
}

template <typename T>
void Deque<T>::addLast(T val) {
	Node<T> *n = new Node<T>;
	n->value = val;
	n->next = NULL;
	n->prev = NULL;
	if (back) {
		Node<T> *p = back;
		p->prev = n;
		back = n;
		back->next = p;
	}
	else {
		back = n;
		front = n;
	}
  _size++;
}

template <typename T>
T Deque<T>::removeFirst() {
	if (front) {
		T val = front->value;
		if (front->prev) {
			Node<T> *n = front;
			front = front->prev;
			delete n;
			front->next = NULL;
		}
		else {
			delete front;
			front = NULL;
			back = NULL;
		}
		_size--;
		return val;
	}
	else {
		throw std::runtime_error("no item in the deque");
	}
}

template <typename T>
T Deque<T>::removeLast() {
	if (back) {
		T val = back->value;
		if (back->next) {
			Node<T> *n = back;
			back = back->next;
			delete n;
			back->prev = NULL;
		}
		else {
			delete back;
			front = NULL;
			back = NULL;
		}
    _size--;
		return val;
	}
	else {
    throw std::runtime_error("no item in the deque");
	}
}

template <typename T>
typename Deque<T>::Iterator Deque<T>::iterator() {
  Deque<T>::Iterator it(front);
  return it;
}

#endif
