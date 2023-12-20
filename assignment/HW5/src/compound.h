#pragma once
#include "./shape.h"
#include "shape_iterator.h"
#include "visitor.h"
#include <vector>
#include <string>
#include "./shape_iterator_factory.h"
#include "./iterator_factory.h"

class Compound : public Shape {
    friend class ShapeIterator;
public:
    Compound() {
    }

    Compound(std::vector<Shape *> shapes): _components(shapes) {

    }

    double perimeter() const override {
        double p = 0.0;
        for (auto component: _components)
            p += component->perimeter();
        return p;
    }

    ShapeIterator * createIterator() override{
        return new ShapeIterator(this);
    }
    ShapeIterator * createIterator(IteratorFactory * factory) override {
        return factory->create();
    }

    void accept(Visitor * visitor) override {
        visitor->visitCompound(this);
    }

    void add(Shape * shape) override {
        _components.push_back(shape);
    }

    std::string toString() const override {
        std::string result("compound { ");

        for (auto component : _components) {
            result += component->toString();
            result += " ";
        }
        result += "}";
        
        return result; 
    }

private: 
    std::vector<Shape *> _components;
};
