#pragma once 

#include<list>

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() {}
    virtual Node * currentItem() const {
        return nullptr;
    }
    virtual void next() {}
    virtual bool isDone() const {
        return true;
    }
};
