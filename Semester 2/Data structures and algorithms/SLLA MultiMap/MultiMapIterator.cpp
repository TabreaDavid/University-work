#include "MultiMapIterator.h"
#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    currentIndex = col.head;
}

TElem MultiMapIterator::getCurrent() const {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    if (!valid())
        throw std::exception();
    return col.elements[currentIndex];
}

bool MultiMapIterator::valid() const {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    return currentIndex != NULL_INDEX;
}

void MultiMapIterator::next() {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    if (!valid())
        throw std::exception();
    currentIndex = col.next[currentIndex];
}

void MultiMapIterator::first() {
    // worst case: Θ(1)
    // best case: Θ(1)
    // average case: Θ(1)
    currentIndex = col.head;
}
