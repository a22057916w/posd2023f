#pragma once

class ShapeIterator;

class IteratorFactory {
public:
    virtual ShapeIterator * create() = 0;
};