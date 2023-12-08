#pragma once

class Triangle;
class Compound;

class Visitor {
public:
    virtual void visitTriangle(Triangle * triangle) = 0;
    virtual void visitCompound(Compound * compound) = 0;
};