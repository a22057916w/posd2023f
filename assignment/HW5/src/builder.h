#pragma once

#include <list>
#include <stack>
#include "triangle.h"
#include "compound.h"

class Builder {
public:
    Builder() {
    }

    void buildTriangle(double a, double b, double c) {
        Shape *triangle = new Triangle(a, b, c);
        if (_compounds.empty()) {
            _shapes.push_back(triangle);
        } else {
            _compounds.top()->add(triangle);
        }
    }

    void buildCompound() {
        _compounds.push(new Compound());
    }

    void endCompound() {
        if (!_compounds.empty()) {
            Shape * compound = _compounds.top();
            _compounds.pop();
            if (_compounds.empty()) {
                _shapes.push_back(compound);
            } else {
                _compounds.top()->add(compound);
            }
        }
    }

    std::list<Shape *> getShapes() const {
        return _shapes;
    }

    void clear() {
        _shapes.clear();
    }

private:
    std::list<Shape *> _shapes;
    std::stack<Shape *> _compounds;
};