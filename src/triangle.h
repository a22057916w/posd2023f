#pragma once 
#include "./shape.h"

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c):_a(a), _b(b), _c(c) { // constructor initialization list 

    }

    double perimeter() const override {
        return _a + _b + _c;
    }

private: 
    double _a, _b, _c;
};