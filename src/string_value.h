#pragma once

#include "value.h"
#include "json_iterator.h"
#include "visitor.h"

#include <string>

using std::string;

class StringValue : public Value {
public:
    StringValue(string value): _value(value) {}

    string toString() override { 
        return  "\"" + _value + "\""; 
    }

    JsonIterator * createIterator() override {
        return new NullIterator();
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitStringValue(this);
    }

private:
    string _value;
};