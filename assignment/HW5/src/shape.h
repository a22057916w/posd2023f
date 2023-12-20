#pragma once

class Visitor;
class ShapeIterator;
class IteratorFactory;
#include <string>

class Shape {
public:
    virtual double perimeter() const = 0; //pure virtual method, declared but not defined
    virtual void accept(Visitor * visitor) {}
    virtual void add(Shape * shape) {}
    virtual std::string toString() const = 0;
    virtual ShapeIterator * createIterator() = 0;
    virtual ShapeIterator * createIterator(IteratorFactory *) = 0;
};