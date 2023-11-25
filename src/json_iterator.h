#pragma once

#include <map>
#include <string>

using std::string;

class Value;

class JsonIterator {
public:
    virtual ~JsonIterator() {}

    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value * currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class NullIterator : public JsonIterator {
public:
    // do nothing
    void first() override {}

    // throw execption
    string currentKey() const override {
        throw string("Null iterator do not has any key.");
    }

    // throw exception
    Value * currentValue() const override {
        throw string("Null iterator do not has any value.");
    }

    // do nothing
    void next() override {}

    // always true
    bool isDone() const override {
        return true;
    } 
};