#ifndef RANQ_H
#define RANQ_H
#include <stdlib.h>
#include <stdexcept>

template <typename T>
struct Node {
 	Node<T> *next;
 	T value;
};

template <typename T>
class RandomizedQueue {
public:
  class Iterator {
  public:
  	Iterator(Node<T>*);
  	Iterator operator++();
    T& operator*();
  private:
  	Node<T> *cur;
  };
	RandomizedQueue();
	bool isEmpty();
	int size();
	void enqueue(T);
	T dequeue();
	T sample();
  RandomizedQueue<T>::Iterator iterator();
private:
	int _size;
  Node<T> *head;
};

template <typename T>
RandomizedQueue<T>::Iterator::Iterator(Node<T> *n) {
  cur = n;
}

// Iterator traverses the node as in singly-linked List
template <typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::Iterator::operator++() {
  if (cur) {
    if (cur->next) { cur = cur->next; }
  }
  return *this;
}

template <typename T>
T& RandomizedQueue<T>::Iterator::operator*() {
  if (cur) {
    return cur->value;
  }
}

template <typename T>
RandomizedQueue<T>::RandomizedQueue() {
	head = NULL;
	_size = 0;
}

template <typename T>
bool RandomizedQueue<T>::isEmpty() {
	return (_size == 0);
}

template <typename T>
int RandomizedQueue<T>::size() {
	return _size;
}

template <typename T>
void RandomizedQueue<T>::enqueue(T val) {
  Node<T> *n = new Node<T>;
  n->value = val;
  n->next = head;
  head = n;
  _size++;
}

template <typename T>
T RandomizedQueue<T>::dequeue() {
  T val;
  if (_size == 0) { throw std::runtime_error("no item in the queue"); }
  else if (_size == 1) {
    val = head->value;
    delete head;
    head = NULL;
    _size--;
    return val;
  }
  else {
    Node<T> *p = head;
    Node<T> *q = head;
    int r = rand() % _size;
    if (r > 0) {
      for (int i = 0; i < r; i++) {
        q = p;
        p = p->next;
      }
      q->next = p->next;
      val = p->value;
      delete p;
    }
    else {
      p = p->next;
      val = q->value;
      delete q;
      head = p;
    }
    _size--;
    return val;
  }
}

template <typename T>
T RandomizedQueue<T>::sample() {
  if (_size == 0) {
    throw std::runtime_error("no item in the deque");
  }
  else {
    Node<T> *n = head;
    int r = rand() % _size;
    for (int i = 0; i < r; i++) {
      n = n->next;
    }
    return n->value;
  }
}

// Shuffles the list and passes the head as iterator.
template <typename T>
typename RandomizedQueue<T>::Iterator RandomizedQueue<T>::iterator() {
  RandomizedQueue<T> temp;
  int max = size();
  for (int i = 0; i < max; i++) {
    T val = dequeue();
    temp.enqueue(val);
  }
  *this = temp;
  typename RandomizedQueue<T>::Iterator it(head);
  return it;
}

#endif