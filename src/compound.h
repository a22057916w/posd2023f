#pragma once
#include "./shape.h"
#include <vector>

class Compound : public Shape {
public:
    Compound(std::vector<Shape *> shapes): _components(shapes) {

    }

    double perimeter() const override {
        double p = 0.0;
        for (auto component: _components)
            p += component->perimeter();
        return p;
    }

private: 
    std::vector<Shape *> _components;
};
