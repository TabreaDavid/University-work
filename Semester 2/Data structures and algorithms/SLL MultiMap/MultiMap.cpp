#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
    head = nullptr;
    length = 0;
}

void MultiMap::add(TKey c, TValue v) {
    Node* newNode = new Node(make_pair(c, v));
    newNode->next = head;
    head = newNode;
    length++;
}

//O(n)
bool MultiMap::remove(TKey keyToRemove, TValue valueToRemove) {
    MultiMapIterator it = this->iterator();
    MultiMap::Node* previousNode = nullptr;
    while (it.valid()) {
        MultiMap::Node* currentNode = it.currentNode;
        if (currentNode->data.first == keyToRemove && currentNode->data.second == valueToRemove) {
            if (previousNode == nullptr) {
                head = currentNode->next;
            } else {
                previousNode->next = currentNode->next; }
            delete currentNode;
            length--;
            return true; 
        }
        previousNode = currentNode;
        it.next(); }
    return false;
}

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> result;
    MultiMapIterator it = this->iterator();

    while (it.valid()) {
        TElem elem = it.getCurrent();
        if (elem.first == c) {
            result.push_back(elem.second);
        }
        it.next();
    }

    return result;
}

int MultiMap::size() const {
    return length;
}

bool MultiMap::isEmpty() const {
    return length == 0;
}

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

int MultiMap::getKeyRange() const {
    if (isEmpty()) {
        return -1;
    }

    MultiMapIterator it = this->iterator();
    TKey minKey = it.getCurrent().first;
    TKey maxKey = minKey;

    while (it.valid()) {
        TKey currentKey = it.getCurrent().first;
        if (currentKey < minKey)
			minKey = currentKey;
        if (currentKey > maxKey)
			maxKey = currentKey;
        it.next();
    }

    return maxKey - minKey;
}

MultiMap::~MultiMap() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
