#pragma once

#include <string>
#include "iterator.h"
#include "iterator_factory.h"
#include "visitor.h"
#include "null_iterator.h"
#include "order_by.h"

#include <iostream>

using namespace std;

class Node {
private:
    string _path;
    Node * _parent;
protected:

    Node(string path): _path(path) {}

public:
    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw string("This node does not support removing sub node");
    }

    string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;
    
    // template method
    void rename(string newName) {   
        if(newName.find("/") == string::npos) {
            size_t pos = _path.find(this->name());
            _path = _path.replace(pos, newName.size(), newName);
        }
        else
            _path = newName;

        renameAllChild(_path);
    }

    // hook operation
    virtual void renameAllChild(string path) {};


    virtual Iterator * createIterator() {
        return new NullIterator();
    }

    virtual Iterator * createIterator(IteratorFactory * factory) {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;

    virtual std::list<string> findByName(string name) = 0;

    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor * visitor) = 0;
};
