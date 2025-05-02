#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentNode = col.head;
}

TElem MultiMapIterator::getCurrent() const {
    if (!valid())
        throw std::exception();
    return currentNode->data;
}

bool MultiMapIterator::valid() const {
    return currentNode != nullptr;
}

void MultiMapIterator::next() {
    if (!valid())
        throw std::exception();
    currentNode = currentNode->next;
}

void MultiMapIterator::first() {
    currentNode = col.head;
}