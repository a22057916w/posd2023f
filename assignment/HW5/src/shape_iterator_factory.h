#pragma once

#include "./shape.h"
#include "./iterator_factory.h"

class ShapeIteratorFactory : public IteratorFactory {
public:
    ShapeIteratorFactory(Shape * compound):_compound(compound) {

    }

    ShapeIterator * create() override{
        return new ShapeIterator(_compound);
    }
private:
    Shape * _compound;
};