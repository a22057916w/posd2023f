#pragma once 
#include "./shape.h"
#include "./visitor.h"
#include "./iterator_factory.h"
#include <string>

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c):_a(a), _b(b), _c(c) { // constructor initialization list 

    }

    double perimeter() const override {
        return _a + _b + _c;
    }

    void accept(Visitor * visitor) override {
        visitor->visitTriangle(this);
    }

    std::string toString() const override {
        std::stringstream ss;
        ss << "triangle " << _a << " " << _b << " " << _c;
        return ss.str();
    }

    ShapeIterator * createIterator() override {
        return nullptr;
    }

    ShapeIterator * createIterator(IteratorFactory * factory) override {
        return nullptr;
    }

private: 
    double _a, _b, _c;
};