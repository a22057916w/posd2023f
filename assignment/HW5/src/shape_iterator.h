#pragma once

#include <vector>

class Shape;
class Compound;

class ShapeIterator {
public:
    ShapeIterator(Shape * compound);
    void first();
    bool isDone() const;
    Shape * currentItem() const;
    void next();

private:
    Compound * _compound;
    std::vector<Shape *>::iterator _it;
};