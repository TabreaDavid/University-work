#include "Stack.h"
#include <exception>

using namespace std;

Stack::Stack() {
	capacity = 20;
	size = 0;
	elements = new TElem[capacity];
}

void Stack::resize(){
	capacity *= 2;
    TElem* newElements = new TElem[capacity];
    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
}

void Stack::push(TElem e) {
	if (size == capacity) {
        resize();
    }
    elements[size++] = e;
}

TElem Stack::top() const {
	if (isEmpty()) {
		throw exception();
    }
    return elements[size - 1];
}

TElem Stack::pop() {
	if (isEmpty()) {
		throw exception();
    }
    return elements[--size];
}


bool Stack::isEmpty() const {
	return size == 0;
}

Stack::~Stack() {
	delete[] elements;
}