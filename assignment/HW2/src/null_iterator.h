#pragma once 

#include "iterator.h"

class NullIterator : public Iterator {
public:
    bool isDone () const override {
        return true;
    }
};