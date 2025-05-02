#include "Queue.h"
#include <iostream>

Queue::Queue() {
    capacity = 20;
    elements = new TElem[capacity];
    front = 0;
    rear = 0;
    size = 0;
}

void Queue::resize() {
    int newCapacity = capacity * 2;
    TElem* newElements = new TElem[newCapacity];

    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[(front + i) % capacity];
    }

    delete[] elements;
    elements = newElements;
    front = 0;
    rear = size;
    capacity = newCapacity;
}

void Queue::push(TElem elem) {
    if (size == capacity)
        resize();

    elements[rear] = elem;
    rear = (rear + 1) % capacity;
    size++;
}

TElem Queue::top() const {
    if (isEmpty()) {
        throw exception();
    }
    return elements[front];
}

TElem Queue::pop() {
    if (isEmpty()) {
        throw exception();
    }

    TElem elem = elements[front];
    front = (front + 1) % capacity;
    size--;

    return elem;
}

bool Queue::isEmpty() const {
    return size == 0;
}

Queue::~Queue() {
    delete[] elements;
}

TElem Queue::getMiddle() const {
    if (isEmpty())
        throw exception();

    int middleIndex = (front + size / 2) % capacity;
    return elements[middleIndex];
}
