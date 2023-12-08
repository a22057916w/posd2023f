#include "shape_iterator.h"
#include "compound.h"
#include "shape.h"

ShapeIterator::ShapeIterator(Shape * compound): _compound(dynamic_cast<Compound *>(compound)) {
    if(_compound == nullptr) {
        throw "Not a compound";
    }   
}

void ShapeIterator::first() {
    _it = _compound->_components.begin();
}

bool ShapeIterator::isDone() const {
    return _it == _compound->_components.end();
}

Shape * ShapeIterator::currentItem() const {
    return *_it;
}

void ShapeIterator::next() {
    _it++;
}