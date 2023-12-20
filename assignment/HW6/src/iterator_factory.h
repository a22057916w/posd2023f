#pragma once

#include "iterator.h"

class Folder;

class IteratorFactory {
public:
    virtual Iterator * create(Folder * node, int operationCount) = 0;
};