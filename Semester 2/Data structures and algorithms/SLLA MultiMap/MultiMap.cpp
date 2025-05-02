#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <iostream>
#include <exception>

using namespace std;

MultiMap::MultiMap() {
    // worst case: Θ(n)
    // best case: Θ(n)
    // average case: Θ(n)
    capacity = 10;
    elements = new TElem[capacity];
    next = new int[capacity];
    head = NULL_INDEX;
    firstFree = 0;
    length = 0;

    for (int i = 0; i < capacity - 1; ++i)
        next[i] = i + 1;

    next[capacity - 1] = NULL_INDEX;
}

bool MultiMap::removeKey(TKey c) {
	// worst case: Θ(n)
    // best case: Θ(n)
    // average case: Θ(n)
    bool removed = false;
    MultiMapIterator it = iterator();

    while (it.valid()) {
        TElem current = it.getCurrent();
        int nextIndex = next[it.currentIndex];  

        if (current.first == c) {
            remove(current.first, current.second);
            removed = true;
            it.currentIndex = nextIndex;  
        } else {
            it.next();
        }
    }

    return removed;
}

vector<TValue> MultiMap::search(TKey c) const {
    // worst case: Θ(n)
    // best case: Θ(n)
    // average case: Θ(n)
    vector<TValue> result;
    MultiMapIterator it = iterator();
    while (it.valid()) {
        TElem current = it.getCurrent();
        if (current.first == c)
            result.push_back(current.second);
        it.next();
    }
    return result;
}

void MultiMap::resize() {
    // worst case: Θ(n)
    // best case: Θ(n)
    // average case: Θ(n)
    int newCapacity = capacity * 2;
    TElem* newElements = new TElem[newCapacity];
    int* newNext = new int[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newElements[i] = elements[i];
        newNext[i] = next[i];
    }
    for (int i = capacity; i < newCapacity - 1; i++)
        newNext[i] = i + 1;
    newNext[newCapacity - 1] = NULL_INDEX;

    delete[] elements;
    delete[] next;

    elements = newElements;
    next = newNext;
    firstFree = capacity;
    capacity = newCapacity;
}

void MultiMap::add(TKey c, TValue v) {
    // worst case: Θ(n) (if resize is triggered)
    // best case: Θ(1)
    // average case: Θ(1) 

	if (firstFree == NULL_INDEX)
        resize();

    int pos = firstFree;
    firstFree = next[firstFree];

    elements[pos] = make_pair(c, v);
    next[pos] = head;
    head = pos;
    length++;
}

bool MultiMap::remove(TKey c, TValue v) {
    // worst case: Θ(n)
    // best case: Θ(1)
    // average case: Θ(n)
    MultiMapIterator it = iterator();
    int previous = NULL_INDEX;

    while (it.valid()) {
        int current = it.currentIndex;

        if (elements[current].first == c && elements[current].second == v) {
            if (previous == NULL_INDEX)
                head = next[current];
            else
                next[previous] = next[current];

			next[current] = firstFree;
    		firstFree = current;
            length--;
            return true;
        }

        previous = current;
        it.next();
    }

    return false;
}


int MultiMap::size() const {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    return length;
}

bool MultiMap::isEmpty() const {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    return length == 0;
}

MultiMapIterator MultiMap::iterator() const {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    delete[] elements;
    delete[] next;
}
