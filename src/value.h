#pragma once

#include <string>

using std::string;

class JsonIterator;
class JsonVisitor;

class Value {
public:
    virtual ~Value() {};
    virtual string toString() = 0;
    virtual JsonIterator * createIterator() = 0;
    virtual void accept(JsonVisitor * visitor) = 0;
protected:
    string _value;
};